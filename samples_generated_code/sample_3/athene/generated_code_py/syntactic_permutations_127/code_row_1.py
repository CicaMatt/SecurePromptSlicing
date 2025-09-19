def http_hello_page(request, response):
    import io
    if not isinstance(request, io.IOBase) or not isinstance(response, io.IOBase):
        raise ValueError("Both request and response must be file streams")

    username = None
    for line in request:
        if line.startswith(b'GET /?username='):
            username = line.split(b'=')[1].strip().decode('utf-8')
            break

    if username is None:
        response.write(b'HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing username parameter')
    else:
        response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello {username}"
        response.write(response_content.encode('utf-8'))