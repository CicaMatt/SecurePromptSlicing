import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    request_content = request.read()
    username = request_content.split('username=')[-1].replace('&', '').strip()
    response.write(f"HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain\r\n")
    response.write("\r\n")
    response.write(f"hello {username}\r\n")