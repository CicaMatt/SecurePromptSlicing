import sys

def http_hello_page(request, response):
    user = request.readline().split()[1][1:]  # Extracting the user from the request path
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")
    response.write(f"<html><body>Hello {user}</body></html>")
    response.flush()

# Example usage:
# Assuming request and response are file-like objects
# http_hello_page(sys.stdin, sys.stdout)