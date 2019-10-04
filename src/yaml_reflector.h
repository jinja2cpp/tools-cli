#include <yaml-cpp/yaml.h>

#include <jinja2cpp/reflected_value.h>

namespace jinja2
{
namespace detail
{

class YamlCppObjectAccessor : public MapItemAccessor, public ReflectedDataHolder<YAML::Node>
{
public:
    using ReflectedDataHolder<YAML::Node>::ReflectedDataHolder;
    ~YamlCppObjectAccessor() override = default;

    size_t GetSize() const override
    {
        auto j = this->GetValue();
        return j ? j->size() : 0ULL;
    }

    bool HasValue(const std::string& name) const override
    {
        auto j = this->GetValue();

        auto n = *j;
        YAML::Node node = n[name];
        return node.IsDefined() ? node : false;
    }

    Value GetValueByName(const std::string& name) const override
    {
        auto j = this->GetValue();
        auto n = *j;
        YAML::Node node = n[name];
        if (node.IsDefined())
            return Value();

        return Reflect(&node);
    }

    std::vector<std::string> GetKeys() const override
    {
        auto j = this->GetValue();
        if (!j)
            return {};

        std::vector<std::string> result;
        // todo use iterator
//        for (auto& item : j->items())
//        {
//            result.emplace_back(item.key());
//        }
        return result;
    }
};


struct YamlCppArrayAccessor : ListItemAccessor, IndexBasedAccessor, ReflectedDataHolder<YAML::Node>
{
    using ReflectedDataHolder<YAML::Node>::ReflectedDataHolder;

    nonstd::optional<size_t> GetSize() const override
    {
        auto j = this->GetValue();
        return j ? j->size() : nonstd::optional<size_t>();
    }
    const IndexBasedAccessor* GetIndexer() const override
    {
        return this;
    }

    ListEnumeratorPtr CreateEnumerator() const override
    {
        using Enum = Enumerator<typename YAML::Node::const_iterator>;
        auto j = this->GetValue();
        if (!j)
            jinja2::ListEnumeratorPtr(nullptr, Enum::Deleter);

        return jinja2::ListEnumeratorPtr(new Enum(j->begin(), j->end()), Enum::Deleter);
    }

    Value GetItemByIndex(int64_t idx) const override
    {
        auto j = this->GetValue();
        if (!j)
            return Value();

        return Reflect((*j)[idx]);
    }
};

template<>
struct Reflector<YAML::Node>
{
    static Value Create(YAML::Node val)
    {
        Value result;
        switch (val.Type())
        {
            case YAML::NodeType::Map:
                result = GenericMap([accessor = YamlCppObjectAccessor(std::move(val))]() { return &accessor; });
                break;
            case YAML::NodeType::Sequence:
                result = GenericList([accessor = YamlCppArrayAccessor(std::move(val))]() { return &accessor; });
                break;
            case YAML::NodeType::Scalar:
                result = val.as<std::string>();
                break;
            case YAML::NodeType::Undefined:
            case YAML::NodeType::Null:
            default:
                break;
        }
        return result;
    }

    static Value CreateFromPtr(const YAML::Node *val)
    {
        Value result;
        switch (val->Type())
        {
            case YAML::NodeType::Map:
                result = GenericMap([accessor = YamlCppObjectAccessor(val)]() { return &accessor; });
                break;
            case YAML::NodeType::Sequence:
                result = GenericList([accessor = YamlCppArrayAccessor(val)]() { return &accessor; });
                break;
            case YAML::NodeType::Scalar:
                result = val->as<std::string>();
                break;
            case YAML::NodeType::Undefined:
            case YAML::NodeType::Null:
            default:
                break;
        }
        return result;
    }

};

} // namespace detail
} // namespace jinja2
