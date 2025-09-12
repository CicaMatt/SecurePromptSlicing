import io

def http_hello_page(request: io.TextIOWrapper, response: io.TextIOWrapper) -> None:
    request_content = request.read()
    username = request_content.split('username=')[1].split('&')[0]
    response.write(f"hello {username}\n")
    response.flush()