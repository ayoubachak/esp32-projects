After Uploading The code 
Open the Serial Prompt to see the private IP 
in my case it was on 192.168.1.110 

## 1) Fisrt Endpoint:
First EndPoint is a get EndPoint from the root URL
```
curl http://192.168.1.110/ -H "Accept: application/json"
```
This will return the following output that you might use on your REST API project
```
{"message":{"Name":"ayoub","LastName":"Achak","Email":"ayoub.achak01@gmail.com"}}
```
## 2) GET Data:
Second EndPoint is /get-message where you append the get params to it.. in this case if the ESP finds the message param it will send it as a response and if not it will send the No parameter message found  
- if you add the "message" parameter to the end of the request:
```
curl -X GET -H "Content-Type: application/json" http://192.168.1.110/get-message?message=This%20is%20my%20message
```
The Output should be 
```
{"message":"This is my message"}
```
- if you the esp can't find the "message" parameter:
```
curl -X GET -H "Content-Type: application/json" http://192.168.1.110/get-message?
```
The Output should be 
```
{"message":"No message parameter"}
```

## 3) POST Data:
You can also send post data to the ESP and it will resend you the same data you sent in this case:
```
curl --location --request POST 'http://192.168.1.110/post-message/' --header 'Content-Type: application/json' --data-raw '{"username":"ayoubachak","password":"thisismypassword"}'
```
if this don't work as wished please try using [Postman](https://www.postman.com/) 
ans set the body to raw and then to json instead of text
