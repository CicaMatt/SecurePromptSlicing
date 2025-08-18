import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nHello {username}\r\n")

request = sys.stdin.buffer
response = sys.stdout.buffer

http_hello_page(request, response)