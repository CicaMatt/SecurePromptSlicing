import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"hello {username}\n")

request = sys.stdin
response = sys.stdout
http_hello_page(request, response)