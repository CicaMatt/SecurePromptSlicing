def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract username from request data (assuming it's sent as a simple text)
    username = request_data.strip()
    
    # Construct the response message
    response_message = f"Hello {username}\n"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage with in-memory streams for demonstration
if __name__ == "__main__":
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    # Move the cursor to the beginning of the response stream and read the output
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))