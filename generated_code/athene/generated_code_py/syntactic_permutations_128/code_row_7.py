import io

def handle_request(request: io.BytesIO, response: io.BytesIO):
    username = request.read().decode('utf-8').strip()
    response.write(f"hello {username}".encode('utf-8'))
    response.seek(0)