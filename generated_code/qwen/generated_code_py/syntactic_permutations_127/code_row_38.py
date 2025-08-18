import io

def http_hello_page(request_stream, response_stream):
    request_data = request_stream.read().decode('utf-8')
    lines = request_data.split('\r\n')
    for line in lines:
        if 'username=' in line:
            username = line.split('=')[1]
            break
    else:
        username = 'Guest'
    
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    response_stream.write(response_message.encode('utf-8'))

# Example usage:
request = io.BytesIO(b'GET /?username=Alice HTTP/1.1\r\nHost: example.com\r\n\r\n')
response = io.BytesIO()

http_hello_page(request, response)

print(response.getvalue().decode('utf-8'))