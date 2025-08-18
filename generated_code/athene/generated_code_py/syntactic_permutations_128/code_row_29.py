def http_hello_page(request, response):
    import io
    if not isinstance(request, io.IOBase) or not isinstance(response, io.IOBase):
        raise ValueError("request and response must be file-like objects")
    
    username = request.readline().strip()  # Read the username from the request
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n")
    response.write(f"<html><body><h1>Hello {username}</h1></body></html>")