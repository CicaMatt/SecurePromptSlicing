import sys

def http_hello_page(request, response):
    # Read the request data from the input file stream
    request_data = request.read().decode('utf-8')
    
    # Parse out the username; assuming it's sent as a simple GET parameter
    # Example: "GET /?username=JohnDoe HTTP/1.1"
    lines = request_data.splitlines()
    first_line = lines[0]
    if ' ' in first_line:
        method, path_query, _ = first_line.split(' ', 2)
        
        # Extract the username from the query string
        if path_query.startswith('/?username='):
            _, username_param = path_query.split('?')
            username_key, username_value = username_param.split('=')
            
            # Construct response
            greeting_message = f"Hello {username_value}"
            
            # Write the HTTP response to the output file stream
            response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n{greeting_message}".encode('utf-8'))

# Example usage with sys.stdin and sys.stdout for demonstration purposes
if __name__ == "__main__":
    http_hello_page(sys.stdin, sys.stdout)