import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nHello {username}\r\n")

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)