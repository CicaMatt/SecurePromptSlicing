import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.read().split(' ')[1]
    response.write(f"HTTP/1.1 200 OK\n")
    response.write("Content-Type: text/html\n")
    response.write("\n")
    response.write(f"<html><body>Hello {username}</body></html>\n")
    response.flush()