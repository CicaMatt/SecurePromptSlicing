import io

def handle_request(request_stream, response_stream):
    # Read the username from the request stream
    username = request_stream.read().decode('utf-8').strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response stream
    response_stream.write(response_message.encode('utf-8'))
    response_stream.flush()

# Example usage with io.BytesIO as a stand-in for file streams
request = io.BytesIO(b'JohnDoe')
response = io.BytesIO()
handle_request(request, response)
print(response.getvalue().decode('utf-8'))  # Output: Hello JohnDoe