class mqtt_client : public object, public mosqpp::mosquittopp {
  bool connected = false;
  var  on_message_callback = nil();
  
 public:

  type_t type() const final { return type_id<mqtt_client>; }
  void   stream_console()      const { runtime::print("mtqq_client"); }

  explicit mqtt_client(std::string host, int port) : mosquittopp("ferret_mqtt_client"){
    mosqpp::lib_init();
    connect_async(host.c_str(), port, 60);
    loop_start();
  }

  void on_connect(int rc){
    /* Only attempt to subscribe on a successful connect. */
    if(rc == 0)
      connected = true;
  }

  var is_connected(){ return obj<boolean>(connected);}

  var publish(var t, var m){
    auto topic = string::to<std::string>(t);
    auto msg   = string::to<std::string>(m);
    int ret = mosquittopp::publish(NULL, topic.c_str(), msg.size(), msg.c_str(), 1, false );
    return obj<boolean>(( ret == MOSQ_ERR_SUCCESS ));
  }
  
  var subscribe(var topic){
    return obj<number>(mosquittopp::subscribe(NULL, string::to<std::string>(topic).c_str()));
  }

  void on_subscribe(uint16_t mid, int qos_count, const uint8_t *granted_qos){ }
  
  void subscribe_callback(var f){ on_message_callback = f; }
  
  void on_message(const struct mosquitto_message *message){
    if (!on_message_callback.is_nil()){
      var topic = obj<string>(std::string(message->topic));

      int len = message->payloadlen;
      char* payload = (char*)message->payload;
      var data = obj<string>();
      for (int i = --len; i >= 0; i--)
        data = data.cast<string>()->cons(obj<number>((payload[i])));
      on_message_callback.cast<lambda_i>()->invoke(runtime::list(topic,data));
    }
  }

  ~mqtt_client(){
    mosqpp::lib_cleanup();
  }
};
