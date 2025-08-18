def handle_request(request_stream, response_stream):
    import io

    # Read the request stream to extract the username
    request_content = request_stream.read().decode('utf-8')
    username = request_content.strip()

    # Construct the response message
    response_message = f"Hello {username}"

    # Write the response to the response file stream
    response_stream.write(response_message.encode('utf-8'))

# Example usage with in-memory streams
if __name__ == "__main__":
    import io

    request_data = "john_doe\n"
    request_stream = io.BytesIO(request_data.encode('utf-8'))
    response_stream = io.BytesIO()

    handle_request(request_stream, response_stream)

    # Print the response from the stream
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))