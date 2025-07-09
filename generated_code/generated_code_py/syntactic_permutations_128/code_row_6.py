import sys
def http_hello_page(request,response):
  req=request.read()
  username=req[len('GET / HTTP/1.1\r\nHost:'):]
  response.write("HTTP/1.1 200 OK\r\n")
  response.write("Hello, " + username)