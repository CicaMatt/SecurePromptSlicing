import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    greeting = f"Hello {username}"
    response.write(greeting)

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)