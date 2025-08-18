import io

def handle_request(request_stream: io.IOBase, response_stream: io.IOBase):
    # Read the request from the client
    request_data = request_stream.read().decode('utf-8').strip()
    
    # Extract the username from the request (assuming it's just a plain string)
    username = request_data
    
    # Construct the greeting message
    response_message = f"hello {username}"
    
    # Write the response to the response stream
    response_stream.write(response_message.encode('utf-8'))

# Example usage:
if __name__ == "__main__":
    # Simulating a client request
    request_content = "JohnDoe"
    request_io = io.StringIO(request_content)
    
    # Prepare an empty response stream
    response_io = io.BytesIO()
    
    # Handle the request
    handle_request(request_io, response_io)
    
    # Output the response content
    print(response_io.getvalue().decode('utf-8'))