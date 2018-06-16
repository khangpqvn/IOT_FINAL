#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <SocketIOClient.h>

SocketIOClient client;
const char *ssid = "HKT Tang 2";    //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char *password = "123456789"; //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.

char host[] = "192.168.5.9"; //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 3000;             //Cổng dịch vụ socket server do chúng ta tạo!

//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// mà chúng ta cần quan tâm đó là
// RID: Tên hàm (tên sự kiện
// Rfull: Danh sách biến (được đóng gói lại là chuối JSON)
extern String RID;
extern String Rfull;
byte mac[6];

//Một số biến dùng cho việc tạo một task
unsigned long previousMillis = 0;
long interval = 2000;

void setup()
{
    //Bật baudrate ở mức 115200 để giao tiếp với máy tính qua Serial
    Serial.begin(9600);
    delay(10);

    //Việc đầu tiên cần làm là kết nối vào mạng Wifi
    Serial.print("Ket noi vao mang ");
    Serial.println(ssid);

    //Kết nối vào mạng Wifi
    WiFi.begin(ssid, password);

    //Chờ đến khi đã được kết nối
    while (WiFi.status() != WL_CONNECTED)
    { //Thoát ra khỏi vòng
        delay(500);
        Serial.print('.');
    }
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);

    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Dia chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());

    if (!client.connect(host, port))
    {
        Serial.println(F("Ket noi den socket server that bai!"));
        return;
    }

    //Khi đã kết nối thành công
    if (client.connected())
    {
        //Thì gửi sự kiện ("connection") đến Socket server ahihi.
        client.send("connection", "message", "Hello");
        // client.postREST("")
    }
}

void loop()
{
    //tạo một task cứ sau "interval" giây thì chạy lệnh:
    if (millis() - previousMillis > interval)
    {
        //lệnh:
        previousMillis = millis();

        //gửi sự kiện "atime" là một JSON chứa tham số message có nội dung là Time please?
        client.send("atime", "message", "Time please?");
    }

    //Khi bắt được bất kỳ sự kiện nào thì chúng ta có hai tham số:
    //  +RID: Tên sự kiện
    //  +RFull: Danh sách tham số được nén thành chuỗi JSON!
    if (client.monitor())
    {
        Serial.println(RID);
        Serial.println(Rfull);
        
    }

    //Kết nối lại!
    if (!client.connected())
    {
        client.reconnect(host, port);
    }
}