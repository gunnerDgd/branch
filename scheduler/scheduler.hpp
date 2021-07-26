#include <branch/context/header/context.hpp>

namespace branch {

    class scheduler
    {
    public:
        virtual void add_branch    (context::context_entity&) = 0;
        virtual void delete_branch (context::context_entity&) = 0;
        
        virtual void schedule      ()                         = 0;
        virtual void schedule      (context::context_entity&) = 0; // Schedule Specified Branch.
        
        virtual void suspend       (context::context_entity&) = 0;  
        virtual void suspend       ()                         = 0; // Suspend Current Running Branch.

        virtual void wake_up       (context::context_entity&) = 0;

    protected:
        context::context_entity* sched_current;
    };
}