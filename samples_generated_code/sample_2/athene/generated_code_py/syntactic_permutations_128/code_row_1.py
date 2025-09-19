def http_hello_page(request, response):
    import io
    if isinstance(request, io.IOBase):
        request_content = request.read().decode('utf-8')
        username = request_content.split('username=')[-1].split('&')[0]
        response.write(f"hello {username}".encode('utf-8'))