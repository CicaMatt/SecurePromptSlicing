import sys
from io import BytesIO

def handle_request(request_stream, response_stream):
    # Read the username from the request stream
    username = request_stream.read().decode('utf-8').strip()
    
    # Construct the response message
    response_message = f"hello {username}\n"
    
    # Write the response to the response stream
    response_stream.write(response_message.encode('utf-8'))

if __name__ == "__main__":
    # Simulate request and response streams using BytesIO
    request_data = "client_username"
    request_stream = BytesIO(request_data.encode('utf-8'))
    response_stream = BytesIO()
    
    # Handle the request
    handle_request(request_stream, response_stream)
    
    # Output the response to standard output
    sys.stdout.buffer.write(response_stream.getvalue())