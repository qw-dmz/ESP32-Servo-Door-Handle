
#include "WebPageManager.h"
#include "DoorManager.h"


AsyncWebServer server(80);
/*******************WEB配置界面*************************/
void setupWebConfig(bool isAoMode) {
	Serial.println("初始化页面中...");
  server.on("/", HTTP_GET, [isAoMode](AsyncWebServerRequest *request) {
    if(isAoMode){
      request->send(200, "text/html", getControlPage());
    }else{
      request->send(200, "text/html", getWebPage());
    }
  }
  );
  // 处理WiFi配置页面
  server.on("/wifi", HTTP_POST, [](AsyncWebServerRequest *request) {
    String ssid = request->arg("ssid");
    String password = request->arg("password");

    // 将SSID和密码保存到Preferences
    Preferences preferences;
    preferences.begin("config", false);
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.end();

    
    // 重启ESP32以应用新的WiFi配置
    ESP.restart();
  });
  // 处理按钮点击事件
  server.on("/control", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasArg("action")) {
      String action = request->arg("action");
      // 处理按钮点击事件
      if (action == "forward") {
        // 处理正转按钮点击事件
        door();
        request->send(200, "text/plain", "Forward");
      } else {
        request->send(400, "text/plain", "Bad Request");
      }
    }
  }
  );
  server.begin();
}
/**************************页面布局*********************************/
String getWebPage() {
  String page = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<style>body {text-align: center; padding: 20px; font-family: 'Arial', sans-serif;";
  page += "background-color: #000; color: #fff;}";
  page += "button {font-size: 18px; padding: 10px 20px; margin: 10px; cursor: pointer;";
  page += "transition: background-color 0.3s ease; border-radius: 20px; border: none;";
  page += "background-color: #ff3333; color: black; box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);";
  page += "position: relative; overflow: hidden;}";
  page += "button:hover {background-color: #cc0000;}";
  page += "button:disabled {background-color: #666; color: #fff;}";
  page += ".progress-bar {position: absolute; top: 0; left: 0; width: 100%; height: 100%;";
  page += "background-color: rgba(255, 255, 255, 0.7); z-index: 1; display: none;}";
  page += ".progress-circle {position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);";
  page += "width: 80px; height: 80px; border-radius: 50%; border: 4px solid #4CAF50;";
  page += "border-top: 4px solid #fff; animation: spin 1s linear infinite;}";
  page += "@keyframes spin {0% { transform: translate(-50%, -50%) rotate(0deg); }";
  page += "100% { transform: translate(-50%, -50%) rotate(360deg); }}</style>";
  page += "</head><body>";
  page += "<h1>C4 引爆器</h1>";
  page += "<button id='openButton' onclick='sendAction(\"forward\")'>引爆</button>";
  page += "<div class='progress-bar' id='progressBar'>";
  page += "<div class='progress-circle'></div><p>正在引爆</p></div>";
  page += "<script>function sendAction(action) {";
  page += "var xhr = new XMLHttpRequest();";
  page += "xhr.open('POST', '/control', true);";
  page += "xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');";
  page += "xhr.send('action=' + action);";
  page += "disableButton(); showProgressBar(); }";
  page += "function disableButton() {";
  page += "var button = document.getElementById('openButton');";
  page += "button.disabled = true;";
  page += "setTimeout(function() { button.disabled = false; hideProgressBar(); }, 10000); }";
  page += "function showProgressBar() {";
  page += "var progressBar = document.getElementById('progressBar');";
  page += "progressBar.style.display = 'block'; }";
  page += "function hideProgressBar() {";
  page += "var progressBar = document.getElementById('progressBar');";
  page += "progressBar.style.display = 'none'; }</script>";
  page += "</body></html>";


  
  /*// WiFi配置表单
  page += "<form action='/wifi' method='post'>";
  page += "SSID: <input type='text' name='ssid' required><br>";
  page += "密码: <input type='password' name='password' required><br>";
  page += "<button type='submit'>重新配置WiFi</button>";
  page += "</form>";
  page += "<button onclick=\"sendAction('forward')\">开门</button>";
  page += "<script>function sendAction(action) {";
  page += "var xhr = new XMLHttpRequest();";
  page += "xhr.open('POST', '/control', true);";
  page += "xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');";
  page += "xhr.send('action=' + action);";
  page += "}</script>";
  page += "</body></html>";
  */
  return page;
}

String getControlPage() {
  String page = "<html><head><meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<style>\n";
  page += "body{text-align:center;padding:20px;font-family:'Arial',sans-serif;}button{font-size:18px;padding:10px 20px;margin:10px;cursor:pointer;transition:background-color 0.3s ease;}button:hover{background-color:#4CAF50;color:white;}</style>";
  page += "</head><body>";
  // WiFi配置表单
  page += "<form action='/wifi' method='post'>";
  page += "<H1>ESP32 配网<H1>";
  page += "SSID: <select name='ssid'>";
  for (const auto& ssid : wifiList) {
    page += "<option value='" + ssid + "'>" + ssid + "</option>";
  }
  page += "</select><br>";
  page += "密码: <input type='password' name='password' required><br>";
  page += "<button type='submit'>配置WiFi</button>";
  page += "</form>";

  // 添加重新扫描按钮
  page += "<form action='/scan' method='get'>";
  page += "<button type='submit'>重新扫描</button>";
  page += "</form>";

  return page;
}

