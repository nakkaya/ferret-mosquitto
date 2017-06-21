(native-header "mosquittopp.h")

(defobject mqtt_client "ferret-mosquitto/mqtt_client_o.h")

(defn connect [host port]
  "__result = obj<mqtt_client>(string::to<std::string>(host), number::to<int>(port));")

(defn connected? [conn]
  "__result = conn.cast<mqtt_client>()->is_connected();")

(defn publish [conn topic msg]
  "__result = conn.cast<mqtt_client>()->publish(topic, msg);")

(defn subscribe [conn topic]
  "__result = conn.cast<mqtt_client>()->subscribe(topic);")

(defn subscribe-callback [conn f]
  "conn.cast<mqtt_client>()->subscribe_callback(f);")
