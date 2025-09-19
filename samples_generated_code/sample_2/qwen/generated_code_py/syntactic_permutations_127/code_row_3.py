def handle_request(request, response):
    import io
    
    # Read the username from the request
    request_data = request.read().decode('utf-8').strip()
    
    # Construct the response
    greeting = f"Hello {request_data}"
    
    # Write the response to the response file stream
    response.write(greeting.encode('utf-8'))
    response.flush()

# Example usage with in-memory streams for demonstration
if __name__ == "__main__":
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()
    
    handle_request(request_stream, response_stream)
    
    # Seek to the beginning of the response stream and read the result
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))