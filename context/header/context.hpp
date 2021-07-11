#include <branch/context/header/types.hpp>

extern "C"
{
    void switch_context (branch::context::context_entity&, branch::context::context_entity&);
    void current_context(branch::context::context_entity&);
}

namespace branch  {
namespace context {

    void BRANCH_PRESERVE switch_to(branch::context::context_entity& prev, branch::context::context_entity& next) { switch_context (prev, next); }
    void                 current  (branch::context::context_entity& curr)                                        { current_context(curr);       }

}
}