def handle_request(request_stream, response_stream):
    import io
    
    # Read the username from the request stream
    request_data = request_stream.read()
    username = request_data.decode('utf-8').strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response stream
    response_stream.write(response_message.encode('utf-8'))
    response_stream.flush()

# Example usage with in-memory streams for demonstration
if __name__ == "__main__":
    request = io.BytesIO(b"JohnDoe")
    response = io.BytesIO()
    
    handle_request(request, response)
    
    # Seek to the beginning of the response stream and read the response
    response.seek(0)
    print(response.read().decode('utf-8'))  # Output: Hello JohnDoe