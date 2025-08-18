import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>Hello {username}</body></html>")

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)