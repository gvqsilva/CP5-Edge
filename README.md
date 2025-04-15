<h1 align="center">Global Vineyard Monitoring with FIWARE and ESP32</h1>

# Table of Contents
* [1 - Project Description](#descricao)
* [2 - Functionality](#funcionalidades)
  * [2.1 - Luminosity Data Capture](#funcionalidades1)
  * [2.2 - Data Transmission to FIWARE](#funcionalidades2)
  * [2.3 - Command Reception via Postman](#funcionalidades3)
  * [2.4 - Historical Data Dashboard](#funcionalidades4)
* [3 - Architecture and Components](#arquitetura)
  * [3.1 - Phisycal Components](#arquitetura1)
  * [3.2 - Communication](#arquitetura2)
  * [3.3 - Software](#arquitetura3)
  * [3.4 - Drawio](#arquitetura4)
* [4 - Dashboard](#dash)
* [5 - System Configuration](#config)
  * [5.1 - FIWARE Setup](#config1)
  * [5.2 - ESP32 Setup](#config2)
  * [5.3 - Python Dashboard Setup](#config3)
* [6 - Available Statistics](#estatisticas)
* [7 - Implementation Steps](#passo-passo)
  * [7.1 - FIWARE Configuration](#passo-passo1)
  * [7.2 - ESP32 Code Deployment](#passo-passo2)
* [8 - License](#licenca)
* [9 - Video](#video)
* [10 - Code Dashboard](#codigo1)
* [10 - Code Simulator](#codigo2)
* [11 - Access to the Simulator](#simulador)

<h2 id="Descricao">Project Description</h2>
<p>This project is part of Check Point 4, aiming to integrate a global vineyard monitoring solution using the FIWARE platform as the backend. The ESP32 DEVKIT 1, equipped with luminosity, humidity, and temperature sensors, collects data from the vineyard environment and sends it to FIWARE for processing and storage. Additionally, a Python-based dashboard is provided for analyzing historical data.</p>
<p>The solution demonstrates interoperability between IoT devices and FIWARE, with control commands sent to the ESP32 through Postman. The dashboard allows for real-time visualization of the vineyard’s environmental conditions and historical data analysis.</p>

<h2 id="funcionalidades">⚙️ System Operation</h2>
<h3 id="funcionalidades1">2.1 Luminosity Data Capture</h3>

- `Feature ` An ESP32 equipped with a luminosity sensor (LDR) captures light intensity data from the vineyard environment.

<h3 id="funcionalidades2">2.2 Data Transmission to FIWARE</h3>

- `Feature ` The captured data is transmitted to a FIWARE instance, where it is processed and stored for further analysis.
  
<h3 id="funcionalidades3">2.3 Command Reception via Postman</h3>

- `Feature ` The system allows for the sending of commands via Postman to the ESP32, such as turning the onboard LED on or off.
  
<h3 id="funcionalidades4">2.4 Historical Data Dashboard</h3>

- `Feature ` A Python-based dashboard allows for the visualization of historical data collected by the sensors, including luminosity, humidity, and temperature, providing a comprehensive overview of vineyard conditions over time.

  <h2 id="arquitetura">🛠️ Architecture and Components</h2> 
<h3 id="arquitetura1">Physical Components</h3> 
<ul> 
  <li>ESP32: Microcontroller that manages the sensors and communication with the MQTT server and the display.</li> 
  <li>DHT 11: Temperature and humidity sensor.</li> 
  <li>LDR: Light-dependent resistor (luminosity sensor).</li> 
  <li>Power supply: for the ESP32.</li> 
</ul> 
<h3 id="arquitetura2">Communication</h3> 
<ul> 
  <li>MQTT Protocol for communication between the ESP32 and FIWARE.</li> 
  <li>Internet connection for communication with FIWARE.</li> 
  <li>Wi-Fi connectivity for the ESP32.</li>
</ul> 
<h3 id="arquitetura3">Software</h3> 
<ul> 
  <li>FIWARE for backend processing and data storage.</li> 
  <li>Postman for sending control commands to the ESP32.</li> 
  <li>Python for creating a dashboard to analyze historical data.</li> 
</ul>
<h3 id="arquitetura4">Drawio</h3> 
<img width="500px" loading="lazy" src = "https://github.com/user-attachments/assets/dad1461a-46c4-4384-97d3-37916407bbfb"/>

<h2 id="dash">Dashboard</h2>
<img width="900px" loading="lazy" src = "https://github.com/user-attachments/assets/b9681d12-ffc8-4f75-8d61-7bb715aee0c3"/>


<h2 id="config">📡 System Configuration</h2> 
<h3 id="config1">FIWARE Setup</h3> 
<ol>
  <li>Install and configure FIWARE using a cloud provider.</li>
  <li>Set up security measures for the FIWARE instance.</li>
  <li>Perform health checks to ensure the instance is functioning properly.</li>
</ol>

<h3 id="config2">ESP32 Setup</h3> 
<ol>
  <li>Program the ESP32 DEVKIT 1 using the provided code.</li>
  <li>Ensure the device is connected to Wi-Fi and able to send data to FIWARE.</li>
</ol>

<h3 id="config3">Python Dashboard Setup</h3> 
<ol>
  <li>Install necessary Python libraries for data visualization.</li>
  <li>Run the dashboard script to visualize historical data collected by the sensors.</li>
</ol>

<h2 id="estatisticas">📊 Available Statistics</h2>
<p>The Python dashboard provides the following statistics:</p>
<ul> 
  <li>Current and historical luminosity levels.</li> 
  <li>Temperature and humidity levels.</li>
  <li>Graphical representation of data trends over time.</li>
</ul>

<h2 id="passo-passo">🚀 Implementation Steps</h2>
<h3 id="passo-passo1">FIWARE Configuration</h3> 
<ol> 
  <li>Download FIWARE Descomplicado and deploy it in a cloud service.</li>
  <li>Configure security measures and verify functionality using health checks.</li>
</ol> 
<h3 id="passo-passo2">ESP32 Code Deployment</h3> 
<ol> 
  <li>Upload the code to the ESP32 using Arduino IDE or another compatible platform.</li> 
  <li>Ensure the sensor data is being transmitted to FIWARE and is accessible.</li>
</ol>

<h2 id="licenca">📄 License</h2> 
<p>This project is licensed under the MIT License. See the LICENSE file for details.</p>

<h2 id="video">Video</h2>
https://youtu.be/50hYxLyjVj8

<h2 id="codigo1">Code Dashboard</h2>
https://github.com/Geral-cp-s/CP5-Edge/blob/main/dashboard.txt

<h2 id="codigo2">Code Simulator</h2> 
https://github.com/Geral-cp-s/CP5-Edge/blob/main/code.ino

<h2 id="Simulador">Access to the Simulator</h2>
https://wokwi.com/projects/410849473799433217
