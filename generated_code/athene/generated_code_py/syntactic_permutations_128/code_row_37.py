import sys

def http_hello_page(request, response):
    username = request.readline().split()[1]  # Assuming the username is sent in the first line of the request
    response.write(f"HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain\r\n")
    response.write("\r\n")  # End of headers
    response.write(f"hello {username}\r\n")

# Example usage:
# http_hello_page(sys.stdin, sys.stdout)