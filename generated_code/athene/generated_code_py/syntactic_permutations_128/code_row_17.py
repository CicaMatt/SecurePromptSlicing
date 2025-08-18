def http_hello_page(request, response):
    import io
    if isinstance(request, io.IOBase):
        username = request.read().decode('utf-8').strip()
        hello_message = f"hello {username}\n"
        response.write(hello_message.encode('utf-8'))