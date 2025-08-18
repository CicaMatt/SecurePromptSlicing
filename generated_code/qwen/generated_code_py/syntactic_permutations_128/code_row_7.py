import sys

def handle_request(request_stream, response_stream):
    username = request_stream.read().strip()
    response = f"hello {username}\n"
    response_stream.write(response.encode())

if __name__ == "__main__":
    handle_request(sys.stdin, sys.stdout)