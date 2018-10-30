/* Branch Monitor - Multi-Core version
 * Marcus Botacin - 2017
 * Federal University of Paran� (UFPR)
 */

#include "config.h"

/* The ISR */

void unhook_handler();
void hook_handler();
void interrupter();

#pragma once /* avoid multiple includes */

/* BTS entries */
typedef struct st_BTSBUFFER
{
	/* from and to addresses
	 * MISC refers to branch prediction and related data
	 */
	UINT64 FROM,TO,CORE;

}TBTS_BUFFER,*PTBTS_BUFFER;

/* DS -- pointer to BTS entries */
typedef struct st_DSBASE
{
	PTBTS_BUFFER BUFFER_BASE,BTS_INDEX,MAXIMUM,THRESHOLD;
	/* if you want to use PEBS, add PEBS entries here */
}TDS_BASE,*PTDS_BASE;

#define NO_PID 0

#define MSR_DEBUGCTL 473

/* Configuration Flags */
#define RTM 1<<15
#define FREEZE_WHILE_SMM_EN 1<<14
#define FREEZE_PERFMON_ON_PMI 1<<12
#define FREEZE_LBRS_ON_PMI 1<<11
#define BTS_OFF_USR 1<<10
#define BTS_OFF_OS 1<<9
#define BTINT 1<<8
#define BTS 1<<7
#define TR 1<<6
#define BTF 1<<1
#define LBR 1<<0
#define BTS_DISABLED 0

#define MSR_DS_AREA 1536
/* Assuming default values */
#define PERF_COUNTER_APIC 0xFEE00340
#define ORIGINAL_APIC_VALUE 254

/* Define how many entries on BTS before generating an interrupt */
#define SIZE_BTS_BUFFER 100
#define THRESHOLD_BTS_BUFFER 25

void FILL_DS_WITH_BUFFER(PTDS_BASE DS_BASE,PTBTS_BUFFER BTS_BUFFER);
void setup_bts(ULONG core);
void bts_cleanup(ULONG core);