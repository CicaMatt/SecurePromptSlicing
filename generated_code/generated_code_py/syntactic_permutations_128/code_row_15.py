import socket

def http_hello_page(request,response):
  #Parse the HTTP Request
  request = socket.socket()
  data = request.recv(1024).decode().split("\n")
  username = data[len(data)-1]
  #Construct an HTTP response
  message = "hello "+username
  response_body = "<html><body>"+message+"</body></html>"
  response_headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n"
  #Send the HTTP Response
  response.sendall(bytes(response_headers,"utf-8"))
  response.sendall(bytes(response_body,"utf-8"))