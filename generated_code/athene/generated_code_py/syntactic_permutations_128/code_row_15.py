import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    request_content = request.read()
    username_start = request_content.find('username=') + 9
    username_end = request_content.find('&', username_start) if '&' in request_content[username_start:] else len(request_content)
    username = request_content[username_start:username_end]
    
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain; charset=utf-8\r\n")
    response.write("\r\n")
    response.write(f"hello {username}\r\n")

# Simulate streams for demonstration purposes
request_stream = io.StringIO('GET /?username=JohnDoe HTTP/1.1\r\nHost: example.com\r\n\r\n')
response_stream = io.StringIO()

http_hello_page(request_stream, response_stream)

print(response_stream.getvalue())

request_stream.close()
response_stream.close()