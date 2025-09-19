import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}\r\n")

# Example usage
request = sys.stdin
response = sys.stdout
http_hello_page(request, response)