import io

def handle_request(request: io.TextIOWrapper, response: io.TextIOWrapper):
    username = request.readline().strip()
    response.write(f"hello {username}\n")
    response.flush()