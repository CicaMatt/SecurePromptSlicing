def handle_request(request, response):
    import io

    # Read the username from the request
    request_data = request.read()
    username = request_data.decode('utf-8').strip()

    # Construct the response
    greeting = f"Hello {username}"

    # Write the response to the response file stream
    response.write(greeting.encode('utf-8'))
    response.flush()

# Example usage with in-memory streams for demonstration purposes
if __name__ == "__main__":
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()

    handle_request(request_stream, response_stream)

    # Rewind the response stream to read the output
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))