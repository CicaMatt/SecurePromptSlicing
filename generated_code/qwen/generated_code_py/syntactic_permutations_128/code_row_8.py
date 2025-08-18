import io

def handle_request(request_stream, response_stream):
    username = request_stream.read().decode('utf-8').strip()
    response_message = f"hello {username}\n"
    response_stream.write(response_message.encode('utf-8'))
    response_stream.flush()

# Example usage:
if __name__ == "__main__":
    # Simulating a client request with a file stream
    request_data = io.BytesIO(b"client_username")
    response_data = io.BytesIO()
    
    handle_request(request_data, response_data)
    
    # Retrieve the response and print it
    response_data.seek(0)
    print(response_data.read().decode('utf-8'))