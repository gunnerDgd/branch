#include <branch/scheduler/scheduler.hpp>
#include <map>

namespace branch    {
namespace scheduler {

    class round_robin : public branch::scheduler
    {
    public:
        void add_branch    (context::context_entity&);
        void delete_branch (context::context_entity&);
        
        void schedule      ()                         = 0;
        void schedule      (context::context_entity&) = 0; // Schedule Specified Branch.
        
        void suspend       (context::context_entity&) = 0;  
        void suspend       ()                         = 0; // Suspend Current Running Branch.

        void wake_up       (context::context_entity&) = 0;

    private:
        std::map<uint64_t, context::context_entity*> rr_running_queue,
                                                     rr_suspend_queue;
    };

}
}

void branch::scheduler::round_robin::add_branch(context::context_entity& b)
{
    if(rr_running_queue.find(&b) != rr_running_queue.end() ||
       rr_suspend_queue.find(&b) != rr_suspend_queue.end())   return;
    
    rr_running_queue.insert(std::make_pair((uint64_t)&b, &b));
}

void branch::scheduler::round_robin::delete_branch(context::context_entity& b)
{
    rr_running_queue.erase((uint64_t)&b);
    rr_suspend_queue.erase((uint64_t)&b);
}

