import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\nContent-Type: text/html\n\n")
    response.write(f"<html><body>Hello {username}</body></html>")