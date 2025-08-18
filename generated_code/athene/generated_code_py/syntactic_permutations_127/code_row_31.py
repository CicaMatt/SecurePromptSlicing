import sys

def http_hello_page(request, response):
    username = request.read().split('username=')[1].strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello {username}")

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)