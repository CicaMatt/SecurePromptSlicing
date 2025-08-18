def http_hello_page(request, response):
    import io
    if isinstance(request, io.IOBase) and isinstance(response, io.IOBase):
        username = request.readline().strip()  # Read the username from the request
        response.write(f"Hello {username}\n")  # Write the greeting to the response