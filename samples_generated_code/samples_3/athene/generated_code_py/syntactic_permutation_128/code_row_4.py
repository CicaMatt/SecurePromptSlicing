import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    request_content = request.read()
    username = request_content.split('username=')[1].split('&')[0]
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}\r\n")