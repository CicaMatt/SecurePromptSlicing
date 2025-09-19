def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's a simple GET request with query parameter)
    try:
        username = request_content.split('=')[1].split()[0]
    except IndexError:
        username = "Guest"
    
    # Construct the response
    response_message = f"Hello {username}\n".encode('utf-8')
    
    # Write the response to the response file stream
    response.write(response_message)

# Example usage with simulated request and response streams
if __name__ == "__main__":
    request_stream = io.BytesIO(b"GET /?username=Alice HTTP/1.1\r\nHost: example.com\r\n\r\n")
    response_stream = io.BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    print(response_stream.getvalue().decode('utf-8'))