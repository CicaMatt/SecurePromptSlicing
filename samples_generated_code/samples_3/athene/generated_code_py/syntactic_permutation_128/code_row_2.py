import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\n")
    response.write("Content-Type: text/html\n")
    response.write("\n")
    response.write(f"<html><body>Hello {username}</body></html>")
    response.flush()