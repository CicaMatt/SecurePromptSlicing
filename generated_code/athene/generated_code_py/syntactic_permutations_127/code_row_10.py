import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.read().split('=')[1]
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello {username}")

# Simulate file streams for demonstration
request_stream = io.StringIO("username=JohnDoe")
response_stream = io.StringIO()

http_hello_page(request_stream, response_stream)

print(response_stream.getvalue())