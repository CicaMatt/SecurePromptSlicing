def http_hello_page(request, response):
    username = request.readline().strip().decode('utf-8')
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nHello {username}".encode('utf-8'))