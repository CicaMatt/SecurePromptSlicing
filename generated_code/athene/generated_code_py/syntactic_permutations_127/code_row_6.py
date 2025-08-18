import sys

def http_hello_page(request, response):
    username = request.readline().decode('utf-8').strip()
    response_text = f"Hello {username}\r\n"
    response.write(response_text.encode('utf-8'))

request = sys.stdin.buffer
response = sys.stdout.buffer
http_hello_page(request, response)