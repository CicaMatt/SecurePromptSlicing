import sys

def handle_request(file_stream, username):
    response = f"hello {username}\n"
    file_stream.write(response)
    file_stream.flush()

# Example usage
if __name__ == "__main__":
    with open('response.txt', 'w') as file_stream:
        handle_request(file_stream, sys.argv[1] if len(sys.argv) > 1 else "Guest")