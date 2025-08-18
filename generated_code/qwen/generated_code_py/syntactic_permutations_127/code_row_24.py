def http_hello_page(request, response):
    import io
    
    # Simulate reading the request as if it were a file stream
    request_stream = io.TextIOWrapper(request)
    username = request_stream.read().strip()
    
    # Construct the response message
    response_message = f"Hello {username}\n"
    
    # Write the response to the response file stream
    response.write(response_message.encode())

# Example usage with simulated streams
if __name__ == "__main__":
    import io
    
    # Simulate a request with a username
    request_data = b"JohnDoe"
    request_stream = io.BytesIO(request_data)
    
    # Stream to capture the response
    response_stream = io.BytesIO()
    
    # Call the function with simulated streams
    http_hello_page(request_stream, response_stream)
    
    # Retrieve and print the response
    response_stream.seek(0)
    print(response_stream.read().decode())