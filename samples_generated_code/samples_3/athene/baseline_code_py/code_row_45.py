import sys

def http_hello_page(request, response):
    username = request.readline().decode('utf-8').strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nhello {username}".encode('utf-8'))

request = sys.stdin.buffer
response = sys.stdout.buffer
http_hello_page(request, response)