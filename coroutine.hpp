#include <branch/branch.hpp>

#include <unordered_set>
#include <any>

namespace  branch    {
    struct branch_node
    {
        branch_node() : branch_parent(nullptr) { }
        
        branch::branch_node                     *branch_parent ;
        branch::context::context_entity         *branch_context;
        std::unordered_set<branch::branch_node*> branch_child  ;
    };

namespace  coroutine {

    template <typename R, typename... Args>
    class coroutine   : public branch::branch
    {
    public:
        coroutine(std::function<R(Args...)> co_exec, Args... co_args)
            : branch::branch(co_exec, co_args) { }
    };

    class  enumerator
    {
    public:
        template <typename T>
        T    advance(branch::coroutine&);

        template <typename T>
        void yield  (T&);

    private:
        std::any            en_yield_value ;
        branch::branch_node en_node                   ,
                           *en_current_node = &en_node;
    };
}
}

template <typename T>
T    branch::coroutine::enumerator::advance(branch::coroutine& co_advance)
{
    auto co_find  = en_current_node->branch_child.find(&co_advance);
    if  (co_find == en_current_node->branch_child.end())
    {
        branch::branch_node* co_new_child = new branch::branch_node;
        co_new_child->branch_parent       = en_current_node        ;
        co_new_child->branch_context      = &co_advance            ;
        
        en_current_node->branch_child.insert(co_new_child);
        en_current_node                    = co_new_child;
        
        co_advance                          .start();
    }
    else
    {
        branch::branch_node* co_prev = en_current_node;
        en_current_node              = *co_find       ;

        branch::context::switch_to    (*en_current_node->branch_context, co_advance);
    }

    return std::any_cast<T>(en_yield_value);
}

template <typename T>
void branch::coroutine::enumerator::yield  (T& co_yield)
{
    branch::branc_node* co_prev = en_current_node;
    en_current_node             = en_current_node->branch_parent;
    
    en_yield_value              = co_yield;
    branch::context::switch_to  (*co_prev->branch_context, *en_current_node->branch_context);
}