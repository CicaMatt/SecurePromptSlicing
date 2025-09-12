import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}\r\n")

if __name__ == "__main__":
    http_hello_page(sys.stdin, sys.stdout)