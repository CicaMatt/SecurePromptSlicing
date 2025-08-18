import sys

def handle_request(request_stream, response_stream):
    username = request_stream.readline().strip()
    response = f"Hello {username}\n"
    response_stream.write(response)

if __name__ == "__main__":
    handle_request(sys.stdin, sys.stdout)