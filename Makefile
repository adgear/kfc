SRCS=src/common.c src/producer.c src/consumer.c src/metadata.c src/kc.c
OBJS=$(SRCS:.c=.o)
BIN=src/kc

.PHONY: doc

all: $(BIN)

include mklove/Makefile.base

# librdkafka must be compiled with -gstrict-dwarf, but kafkacat must not,
# due to some clang bug on OSX 10.9
CPPFLAGS := $(subst strict-dwarf,,$(CPPFLAGS))

install: bin-install install-man

install-man:
	echo $(INSTALL) -d $$DESTDIR$(man1dir) && \
	echo $(INSTALL) doc/kafkacat.1 $$DESTDIR$(man1dir)

doc:
	$(MAKE) -C doc

clean: bin-clean

-include $(DEPS)
