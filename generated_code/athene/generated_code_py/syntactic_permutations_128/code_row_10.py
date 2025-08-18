import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    request_content = request.read()
    username_start = request_content.find('username=') + len('username=')
    username_end = request_content.find('&', username_start) if '&' in request_content[username_start:] else None
    username = request_content[username_start:username_end]
    
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain; charset=utf-8\r\n")
    response.write("\r\n")  # End of headers
    response.write(f"hello {username}\r\n")
    response.flush()