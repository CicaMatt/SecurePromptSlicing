import os

def http_hello_page(request, response):
    username = request.readline().decode('utf-8').strip()
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello {username}\r\n".encode('utf-8')
    response.write(response_content)
    response.flush()