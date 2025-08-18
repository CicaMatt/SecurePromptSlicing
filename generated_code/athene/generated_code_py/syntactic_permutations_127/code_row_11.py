import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.read().split('username=')[1]
    if '&' in username:
        username = username.split('&')[0]
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>Hello {username}</body></html>")