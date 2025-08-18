import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    request_data = request.read()
    username_start = request_data.find('username=') + len('username=')
    username_end = request_data.find('&', username_start)
    if username_end == -1:
        username_end = len(request_data)
    username = request_data[username_start:username_end]
    response.write(f"HTTP/1.1 200 OK\nContent-Type: text/plain\n\nhello {username}\n")