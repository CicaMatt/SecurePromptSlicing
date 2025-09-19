import sys

def http_hello_page(request, response):
    username = request.readline().decode('utf-8').strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n")
    response.write(f"<html><body>Hello {username}</body></html>")
    response.flush()

if __name__ == "__main__":
    http_hello_page(sys.stdin.buffer, sys.stdout.buffer)