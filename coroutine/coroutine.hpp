#include <branch/branch.hpp>

#include <unordered_map>
#include <any>

namespace  branch    {
namespace  coroutine {

    struct coroutine_node : public context::context_entity
    {
        coroutine_node(context::context_entity& co_context         ,
                       coroutine_node         * co_parent = nullptr) 
            : branch_parent (co_parent) ,
              branch_context(co_context){ }
        
        coroutine_node                               *branch_parent ;
        context::context_entity                      &branch_context;
        std::unordered_map<uint64_t, coroutine_node*> branch_child  ; // Key : Address of branch::branch<R(Args...)>
    };

    class  enumerator
    {
    public:
        enumerator()                    { en_node.branch_context = new context::context_entity; }

        template <typename T, typename R, typename... Args>
        T    advance(branch<R(Args...)>&);

        template <typename T>
        void yield  (T);

    private:
        std::any       en_yield_value            ;
        coroutine_node en_node                   ,
                      *en_current_node = &en_node;
    };
}
}

template <typename T, typename R, typename... Args>
T    branch::coroutine::enumerator::advance(branch<R(Args...)>& co_advance)
{
    auto co_find  = en_current_node->branch_child.find((uint64_t)&co_advance);
    if  (co_find == en_current_node->branch_child.end())
    {
        coroutine_node* co_new_child = new coroutine_node(co_advance, en_current_node),
                      * co_prev      = en_current_node                                ;
        
        en_current_node->branch_child.insert(std::make_pair((uint64_t)&co_advance, co_new_child));
        en_current_node                                                          = co_new_child  ;
        
        co_advance.start(*co_prev->branch_context);
    }
    else
    {
        coroutine_node* co_prev = en_current_node;
        en_current_node         = (*co_find).second;

        context::switch_to    (*en_current_node->branch_context, co_advance);
    }

    return std::any_cast<T>(en_yield_value);
}

template <typename T>
void branch::coroutine::enumerator::yield  (T co_yield)
{
    coroutine_node* co_prev = en_current_node;
    en_current_node         = en_current_node->branch_parent;
    
    en_yield_value          = co_yield;
    context::switch_to      (*co_prev->branch_context, *en_current_node->branch_context);
}