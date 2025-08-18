def http_hello_page(request, response):
    import io
    if isinstance(request, io.TextIOWrapper) and isinstance(response, io.BufferedWriter):
        username = request.readline().strip()
        greeting = f"hello {username}\r\n"
        response.write(f"HTTP/1.1 200 OK\r\nContent-Length: {len(greeting)}\r\n\r\n{greeting}")
        response.flush()