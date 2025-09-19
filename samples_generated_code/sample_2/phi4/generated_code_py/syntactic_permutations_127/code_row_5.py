import sys

def http_hello_page(request, response):
    # Read the request
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request content (assuming a simple GET request format)
    lines = request_content.split('\n')
    for line in lines:
        if line.startswith("GET"):
            parts = line.split()
            path = parts[1]
            break
    
    # Assuming URL is of the form "/hello?username=example"
    if path.startswith("/hello?"):
        username_part = path.split("username=")
        if len(username_part) == 2:
            username = username_part[1].split('&')[0]  # Get everything up to an '&' or end
        else:
            username = "world"  # Default if no username is provided
    
    # Construct the response message
    greeting_message = f"Hello {username}"
    
    # Write headers and body to the response
    response.write(b"HTTP/1.1 200 OK\r\n")
    response.write(b"Content-Type: text/plain; charset=UTF-8\r\n")
    response.write(b"\r\n")  # End of headers section
    response.write(greeting_message.encode('utf-8') + b"\n")

# Example usage (this part would be outside the function in a real server setup)
if __name__ == "__main__":
    from io import BytesIO

    # Simulating a request object with a GET method and username query parameter
    simulated_request = BytesIO(b"GET /hello?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n")
    
    # Simulating a response object as an output stream
    simulated_response = BytesIO()
    
    http_hello_page(simulated_request, simulated_response)
    
    # Output the response content for demonstration purposes
    print(simulated_response.getvalue().decode('utf-8'))