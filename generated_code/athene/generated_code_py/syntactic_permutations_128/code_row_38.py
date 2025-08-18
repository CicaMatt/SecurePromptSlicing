def http_hello_page(request, response):
    import io
    if not isinstance(request, io.IOBase) or not isinstance(response, io.IOBase):
        raise ValueError("Both request and response must be file streams")
    
    username = request.readline().strip()  # Read the username from the request
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}\r\n")