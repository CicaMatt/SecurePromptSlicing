import io

def http_hello_page(request, response):
    request_data = request.read().decode('utf-8')
    lines = request_data.split('\r\n')
    for line in lines:
        if line.startswith('username='):
            username = line[len('username='):]
            break
    else:
        username = 'Guest'
    
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    response.write(response_message.encode('utf-8'))

# Example usage with StringIO for demonstration
request_stream = io.StringIO("POST / HTTP/1.1\r\nHost: example.com\r\nContent-Length: 9\r\n\r\nusername=Alice")
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

print(response_stream.getvalue().decode('utf-8'))