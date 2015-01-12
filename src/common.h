#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

#include <librdkafka/rdkafka.h>

typedef struct {
  int     run;
  int     verbosity;
  int     exitcode;
  char    mode;
  int     flags;
#define CONF_F_KEY_DELIM  0x2
#define CONF_F_OFFSET     0x4 /* Print offsets */
#define CONF_F_TEE  0x8 /* Tee output when producing */
  int     delim;
  int     key_delim;
  int     msg_size;
  char   *brokers;
  char   *topic;
  int32_t partition;
  int64_t offset;
  int     exit_eof;
  int64_t msg_cnt;
  FILE  **inputs;
  int     n_inputs;
  FILE   *fd_err;

  rd_kafka_conf_t       *rk_conf;
  rd_kafka_topic_conf_t *rkt_conf;

  rd_kafka_t      *rk;
  rd_kafka_topic_t      *rkt;

  char   *debug;
  int     conf_dump;
} conf_t;

conf_t conf;

typedef struct {
  uint64_t tx;
  uint64_t tx_err_q;

  uint64_t rx;
} stats_t;

stats_t stats;

void term(int sig);

void set_signals();

void __attribute__((noreturn)) fatal0(const char *func, int line,
                                      const char *fmt, ...);

#define FATAL(fmt...)  fatal0(__FUNCTION__, __LINE__, fmt)

/* Info printout */
#define INFO(VERBLVL,FMT...) do {                    \
                if (conf.verbosity >= (VERBLVL))     \
                        fprintf(stderr, "%% " FMT);  \
        } while (0)

int parse_delim (const char *str);


void __attribute__((noreturn)) usage (const char *argv0, int exitcode,
                                      const char *reason);

void kc_rdkafka_init(rd_kafka_type_t type);
