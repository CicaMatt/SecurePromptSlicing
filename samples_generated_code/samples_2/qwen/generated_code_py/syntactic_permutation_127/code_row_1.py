def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract username from the request (assuming it's sent as plain text)
    username = request_data.strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage with simulated streams
if __name__ == "__main__":
    import io
    
    # Simulate a request with a username
    request_stream = io.BytesIO(b"JohnDoe")
    
    # Prepare a response stream
    response_stream = io.BytesIO()
    
    # Call the function with simulated streams
    http_hello_page(request_stream, response_stream)
    
    # Seek to the beginning of the response stream and read the response
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))