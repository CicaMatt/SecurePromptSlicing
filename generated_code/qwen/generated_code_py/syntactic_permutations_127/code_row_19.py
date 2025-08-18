import io

def http_hello_page(request_stream, response_stream):
    request_data = request_stream.read().decode('utf-8')
    lines = request_data.split('\r\n')
    for line in lines:
        if 'username=' in line:
            username = line.split('username=')[1].split('&')[0]
            break
    else:
        username = 'Guest'
    
    response = f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello {username}"
    response_stream.write(response.encode('utf-8'))

# Example usage with file streams
request = io.BytesIO(b'GET /?username=John HTTP/1.1\r\nHost: example.com\r\n\r\n')
response = io.BytesIO()
http_hello_page(request, response)
print(response.getvalue().decode('utf-8'))