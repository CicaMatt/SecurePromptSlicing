def http_hello_page(request, response):
    import io
    
    if isinstance(request, io.IOBase) and isinstance(response, io.IOBase):
        username = request.readline().strip()  # Read the username from the request
        response.write(f"HTTP/1.1 200 OK\r\n")
        response.write("Content-Type: text/plain\r\n")
        response.write("\r\n")  # End of headers
        response.write(f"hello {username}\r\n")