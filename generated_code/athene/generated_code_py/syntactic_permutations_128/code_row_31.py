import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    request_content = request.read()
    username_start = request_content.find('username=') + 9
    username_end = request_content.find('&', username_start)
    if username_end == -1:
        username_end = len(request_content)
    username = request_content[username_start:username_end]
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nhello {username}\r\n")