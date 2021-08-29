#include <branch/header/context.hpp>

#include <sys/mman.h>
#include <type_traits>

#define BRANCH_STACK_SIZE 8192

namespace branch {

    class default_memory_allocator
    {
    public:
        static void* allocate  (size_t size)             { return mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); }
        static void  deallocate(size_t size, void* addr) { munmap(addr, size); }
    };
    
    template <typename MemoryAllocater = default_memory_allocator>
    class branch
    {
    public:
        template <typename M, typename Fp, typename... Args>
        branch (branch<M>& prev, Fp branch_fp, Args&&... branch_args);
        branch ()                                                  { context_store_stack         (branch_context.stack_context); }
        ~branch()                                                  { MemoryAllocater::deallocate(BRANCH_STACK_SIZE, branch_stack); }

        context::context_entity& get_context() { return branch_context; }

    public:
        template <typename M>
        void operator()(branch<M>& next) { context::switch_to(branch_context, next.get_context()); }

    protected:
        void*                   branch_stack  ;
        context::context_entity branch_context;
    };
}

template <typename MemoryAllocater>
template <typename M, typename Fp, typename... Args>
branch::branch<MemoryAllocater>::branch(branch<M>& prev, Fp branch_fp, Args&&... branch_args)
    : branch_stack(MemoryAllocater::allocate(BRANCH_STACK_SIZE)) 
{
    branch_context.stack_context.rsp = (uint64_t)branch_stack + BRANCH_STACK_SIZE;
    branch_context.stack_context.rbp = branch_context.stack_context.rsp;

    context::execution_argument<Fp, branch<MemoryAllocater>&, Args...> exec_args(branch_fp, *this, branch_args...);
    context::execute_to                                                         (prev.get_context(), branch_context, exec_args);
}