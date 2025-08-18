import io

def http_hello_page(request, response):
    request_data = request.read().decode('utf-8')
    lines = request_data.split('\n')
    for line in lines:
        if 'username=' in line:
            username = line.split('=')[1].strip()
            break
    else:
        username = "Guest"
    
    response_message = f"Hello {username}"
    response.write(response_message.encode('utf-8'))

# Example usage
request_stream = io.BytesIO(b'GET /?username=Alice HTTP/1.1\r\nHost: example.com\r\n\r\n')
response_stream = io.BytesIO()
http_hello_page(request_stream, response_stream)
print(response_stream.getvalue().decode('utf-8'))