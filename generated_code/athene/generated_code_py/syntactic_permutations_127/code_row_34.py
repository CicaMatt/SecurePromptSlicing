import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n")
    response.write(f"<html><body>Hello {username}</body></html>")

if __name__ == "__main__":
    http_hello_page(sys.stdin, sys.stdout)