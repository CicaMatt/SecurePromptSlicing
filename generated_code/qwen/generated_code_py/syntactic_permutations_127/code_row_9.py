def http_hello_page(request_stream, response_stream):
    import io
    
    # Read the request content
    request_content = request_stream.read().decode('utf-8')
    
    # Extract username from the request (assuming simple format: "username=[value]")
    try:
        username = request_content.split('=')[1]
    except IndexError:
        username = "Guest"
    
    # Construct the response
    response_message = f"Hello {username}"
    
    # Write the response to the response stream
    response_stream.write(response_message.encode('utf-8'))
    response_stream.flush()

# Example usage with in-memory streams for demonstration
if __name__ == "__main__":
    request = io.BytesIO(b"username=Alice")
    response = io.BytesIO()
    
    http_hello_page(request, response)
    
    print(response.getvalue().decode('utf-8'))  # Output: Hello Alice