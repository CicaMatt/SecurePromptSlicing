import io

def handle_request(request: io.BufferedReader, response: io.BufferedWriter):
    username = request.readline().strip()
    response.write(f"Hello {username}\n")
    response.flush()