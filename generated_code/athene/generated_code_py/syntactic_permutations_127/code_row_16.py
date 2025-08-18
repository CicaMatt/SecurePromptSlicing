def http_hello_page(request, response):
    import io
    if isinstance(request, io.IOBase) and isinstance(response, io.IOBase):
        username = request.readline().strip()  # assuming username is on the first line
        response.write(f"Hello {username}\r\n")