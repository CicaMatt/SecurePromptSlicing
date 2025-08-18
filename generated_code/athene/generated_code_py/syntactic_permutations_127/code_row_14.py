def http_hello_page(request, response):
    username = request.readline().strip()  # Read the username from the request
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n")
    response.write(f"<html><body>Hello {username}</body></html>")