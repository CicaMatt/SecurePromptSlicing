import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\n")
    response.write(f"Content-Type: text/html; charset=utf-8\r\n")
    response.write(f"\r\n")
    response.write(f"<html><body>Hello {username}</body></html>\r\n")

# Example usage
request = sys.stdin
response = sys.stdout
http_hello_page(request, response)