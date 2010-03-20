#ifndef EXEC_SPARC_H
#define EXEC_SPARC_H 1
#include "config.h"
#include "dyngen-exec.h"

#if defined(CONFIG_TCG_INTERPRETER)
extern struct CPUSPARCState *env;
#else
register struct CPUSPARCState *env asm(AREG0);
#endif

#define DT0 (env->dt0)
#define DT1 (env->dt1)
#define QT0 (env->qt0)
#define QT1 (env->qt1)

#include "cpu.h"
#include "exec-all.h"

/* op_helper.c */
void do_interrupt(CPUState *env);

static inline int cpu_has_work(CPUState *env1)
{
    return (env1->interrupt_request & CPU_INTERRUPT_HARD) &&
           cpu_interrupts_enabled(env1);
}


static inline int cpu_halted(CPUState *env1) {
    if (!env1->halted)
        return 0;
    if (cpu_has_work(env1)) {
        env1->halted = 0;
        return 0;
    }
    return EXCP_HALTED;
}

#endif
