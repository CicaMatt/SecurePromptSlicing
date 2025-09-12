def handle_request(request_stream, response_stream):
    # Read the request and extract the username
    request_data = request_stream.read().decode('utf-8')
    username = request_data.strip()

    # Construct the greeting message
    response_message = f"Hello {username}"

    # Write the response to the response file stream
    response_stream.write(response_message.encode('utf-8'))

# Example usage (requires actual streams for real execution)
if __name__ == "__main__":
    import io

    # Simulating a request with a username "Alice"
    request_data = io.BytesIO(b"Alice")
    
    # Creating an in-memory stream to capture the response
    response_data = io.BytesIO()

    handle_request(request_data, response_data)

    # Resetting the pointer of the response stream to the beginning
    response_data.seek(0)
    print(response_data.read().decode('utf-8'))  # Output should be: Hello Alice