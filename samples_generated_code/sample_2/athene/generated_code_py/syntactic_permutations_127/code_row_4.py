import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.readline().strip()
    response.write(f"Hello {username}\n")