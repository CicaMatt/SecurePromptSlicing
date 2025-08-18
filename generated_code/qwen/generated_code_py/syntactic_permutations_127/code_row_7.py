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

# Example usage with BytesIO for demonstration purposes
from io import BytesIO

request = BytesIO(b'john_doe')
response = BytesIO()

handle_request(request, response)

print(response.getvalue().decode('utf-8'))  # Output: Hello john_doe