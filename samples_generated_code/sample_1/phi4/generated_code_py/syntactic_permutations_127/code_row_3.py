import io

def handle_client_request(request_stream: io.StringIO, response_stream: io.StringIO):
    # Read the username from the request
    username = request_stream.read().strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response_stream.write(response_message)

# Example usage:
request_data = io.StringIO("Alice")
response_data = io.StringIO()

handle_client_request(request_data, response_data)
print(response_data.getvalue())