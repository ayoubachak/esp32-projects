## ESP Wifi Setup
The goal of this project is to setup connection for wifi on the esp32 with a graphical interface.
## Workflow
When the esp is turns on for the first time.. it's not yet connected to the wifi so:
- Wait 30 seconds while the esp tries to connect (it will not)
- It will open and AP ( Access Point ) called ```ESP69``` with password ```123456789```
- Connect to the AP and Goto [http://192.168.4.1/][http://192.168.4.1/]
- Enter the Wifi Credentials in the form and hit save
- The esp will take the form data and store it with the EPROM Library
- Hit the Reset Button on the ESP.. it should read the wifi credentials from the EPROM and connect to the wifi automatically
Since you are connected now.. you can send requests to external servers