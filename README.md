kfc(1) -- kafka client
======================

Copyright (c) 2015, François Saint-Jacques

Copyright (c) 2014, Magnus Edenhill

https://github.com/fsaintjacques/kfc

A custom fork of

https://github.com/edenhill/kafkacat

`kfc` is a generic non-JVM producer and consumer for Apache Kafka 0.8;
think of it as a netcat for Kafka.

In `producer` mode, `kfc` reads messages from standard input, delimited with a
configurable character, and produces them to the provided topic.

In `consumer` mode, `kfc` reads messages from a topic and
prints them to standard output.

`kfc` also features a metadata list command to display the current
state of the Kafka cluster and its topics and partitions.

`kfc` is fast and lightweight; statically linked, it is no more than 150KB.

REQUIREMENTS
------------

 * librdkafka - https://github.com/edenhill/librdkafka

BUILD
-----

    ./configure
    make
    sudo make install

QUICK BUILD
===========

The tools/bootstrap.sh build script will download and build the required
dependencies, providing a quick and easy means of building `kfc`.
This script requires internet connectivity and git.
The resulting `kfc` binary will be linked statically to avoid runtime
dependencies.

    tools/bootstrap.sh

EXAMPLES
--------

* Produce a single message:

```
    $ echo "test message" | kfc producer test
```

* Consume the last message:

```
    $ kfc consumer -e -o -1 test
    test message
```

* Show metadata on topic `test`:

```
    $ kfc metadata test
    {
      "brokers": [
        { "id":0, "host":"localhost:9092" }
      ],
      "topics": [
        {
          "name": "test",
          "partitions": [
            { "id": 0, "leader": 0, "replicas": [0], "isrs": [0] }
          ]
        }
      ]
    }
```

DOCUMENTATION
-------------

See doc/kfc.md for complete documentation.
