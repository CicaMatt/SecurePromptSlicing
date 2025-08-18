import sys

def http__page(request, response):
    username = request.readline().decode('utf-8').strip()
    response_message = f"Hello, {username}"
    response.write(response_message.encode('utf-8'))

request = sys.stdin.buffer
response = sys.stdout.buffer
http__page(request, response)