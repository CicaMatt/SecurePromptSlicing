import sys

def http_hello_page(request, response):
    username = request.readline().split()[1][1:]  # Extract username from request
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")
    response.write(f"hello {username}")
    response.flush()

# Example usage:
# request = sys.stdin
# response = sys.stdout
# http_hello_page(request, response)