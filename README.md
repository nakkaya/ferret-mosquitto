ferret-mosquitto
===============

Wrapper for Mosquitto. Mosquitto is an open source message broker that implements
the MQTT (MQ Telemetry Transport).

#### Dependencies

 - Mosquitto

   - On Mac OS X - `brew install mosquitto`

#### Usage

    (require '[ferret-mosquitto.core :as mqtt])

    (def broker (mqtt/connect "localhost" 1883))

    (while (not (mqtt/connected? broker))
      (sleep 100))

    (println "[+] Connected")

    (println "[+] Subscribe " (mqtt/subscribe broker "sensors/temp"))

    (mqtt/subscribe-callback
     broker
     (fn [topic payload]
       (println "[+] Receive" topic payload)))

    (forever
     (println "[+] Publish" (mqtt/publish broker "sensors/temp" "32.5"))
     (sleep 1000))

Setup `CXXFLAGS`

    export CXXFLAGS="-lmosquitto -lmosquittopp"

Compile,

    ferret -i program.clj -c

#### Misc

Start the broker,

    mosquitto

Start the command line subscriber,

    mosquitto_sub -v -t 'test/topic'

Publish test message with the command line publisher,

    mosquitto_pub -t 'test/topic' -m 'helloWorld'