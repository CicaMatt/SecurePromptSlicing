def http_hello_page(request, response):
    import io
    if isinstance(request, io.IOBase):
        request_content = request.read().decode('utf-8')
        username = request_content.split('=')[1]  # Assuming a simple key=value format
        response.write(f"hello {username}".encode('utf-8'))