import sys

def http_hello_page(request, response):
    name = request.readline().split()[1][1:]  # Extracting the name from the request line
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")
    response.write(f"hello {name}")
    response.flush()

# Example usage:
# with open('request.txt', 'r') as req, open('response.txt', 'w') as res:
#     http_hello_page(req, res)