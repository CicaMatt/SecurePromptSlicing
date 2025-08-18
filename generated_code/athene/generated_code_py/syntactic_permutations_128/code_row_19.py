import os

def http_hello_page(request, response):
    username = request.readline().decode('utf-8').strip()
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>Hello {username}</body></html>".encode('utf-8'))
    response.flush()