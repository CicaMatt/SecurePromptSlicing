def http_hello_page(request, response):
    import io
    if not isinstance(request, io.IOBase) or not isinstance(response, io.IOBase):
        raise ValueError("request and response must be file streams")
    
    request_content = request.read().decode('utf-8')
    username = request_content.split('username=')[-1].split('&')[0]
    
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nhello {username}"
    response.write(response_content.encode('utf-8'))