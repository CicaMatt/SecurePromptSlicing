import sys

def http_hello_page(request, response):
    username = request.readline().split()[1]
    response.write(f"HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain\r\n")
    response.write("\r\n")
    response.write(f"hello {username}\r\n")

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)