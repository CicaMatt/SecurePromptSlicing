import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain; charset=utf-8\r\n")
    response.write("\r\n")
    response.write(f"Hello {username}\r\n")

if __name__ == "__main__":
    http_hello_page(sys.stdin, sys.stdout)