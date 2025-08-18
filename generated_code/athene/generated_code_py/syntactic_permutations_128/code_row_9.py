import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.read().split(' ')[1]
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}")

request = io.StringIO("GET /john_doe HTTP/1.1")
response = io.StringIO()
http_hello_page(request, response)

print(response.getvalue())