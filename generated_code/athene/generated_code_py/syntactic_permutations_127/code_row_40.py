import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"Hello {username}\r\n")

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)