def http_hello_page(request, response):
    # Read the request data (assuming it's in a simple format for demonstration)
    import io

    request_stream = io.TextIOWrapper(request)
    
    # Extract the username from the request (for simplicity assume it's the first line of the stream)
    request_lines = request_stream.readlines()
    if len(request_lines) > 0:
        # Assume the first line contains "username=<name>"
        header_line = request_lines[0].strip()
        if header_line.startswith("username="):
            username = header_line.split('=')[1]
            
            # Construct the response
            response_content = f"Hello {username}"
            
            # Write the response to the response file stream
            response_stream = io.TextIOWrapper(response)
            response_stream.write(f"Content-Length: {len(response_content)}\r\n")
            response_stream.write("\r\n")
            response_stream.write(response_content)
    
    request.close()
    response.close()

# Example usage (note: this is for demonstration purposes and not a real HTTP server setup):
import io

request_data = io.BytesIO(b"username=JohnDoe\r\n")
response_data = io.BytesIO()

http_hello_page(request_data, response_data)

print(response_data.getvalue().decode())