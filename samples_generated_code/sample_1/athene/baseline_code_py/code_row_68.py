import sys

def http_hello_page(request, response):
    username = request.readline().decode('utf-8').strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nhello {username}".encode('utf-8'))

if __name__ == "__main__":
    http_hello_page(sys.stdin.buffer, sys.stdout.buffer)