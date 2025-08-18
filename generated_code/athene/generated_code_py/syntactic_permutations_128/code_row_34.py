import sys

def http_hello_page(request, response):
    username = request.readline().split()[1]  # Assuming the username is passed as part of the first line
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")  # End of headers
    response.write(f"<html><body>Hello {username}</body></html>\r\n")

# Example usage (simulating file streams with sys.stdin and sys.stdout)
if __name__ == "__main__":
    http_hello_page(sys.stdin, sys.stdout)