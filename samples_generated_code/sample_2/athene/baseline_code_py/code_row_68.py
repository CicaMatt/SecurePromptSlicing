import sys

def http_hello_page(request, response):
    username = request.readline().split()[1]  # Extract username from the request
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain\r\n")
    response.write("\r\n")
    response.write(f"hello {username}\r\n")

# Example usage:
# request = open('request.txt', 'r')
# response = open('response.txt', 'w')
# http_hello_page(request, response)
# request.close()
# response.close()