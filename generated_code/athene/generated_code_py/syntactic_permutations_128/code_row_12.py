import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper) -> None:
    username = request.readline().strip()
    response.write(f"hello {username}\n")
    response.flush()