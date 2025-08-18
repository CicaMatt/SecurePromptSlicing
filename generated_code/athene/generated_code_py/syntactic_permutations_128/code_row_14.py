import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")
    response.write(f"<html><body>Hello {username}</body></html>\r\n")

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)