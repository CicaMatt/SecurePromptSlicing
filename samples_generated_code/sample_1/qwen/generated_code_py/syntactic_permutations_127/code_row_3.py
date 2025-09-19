def handle_request(request, response):
    import io
    
    # Read the username from the request
    request_data = request.read().decode('utf-8').strip()
    
    # Construct the response
    greeting = f"Hello {request_data}"
    
    # Write the response to the response file stream
    response.write(greeting.encode('utf-8'))
    response.flush()

# Example usage with in-memory streams for demonstration purposes
if __name__ == "__main__":
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()
    
    handle_request(request_stream, response_stream)
    
    print(response_stream.getvalue().decode('utf-8'))  # Output: Hello JohnDoe