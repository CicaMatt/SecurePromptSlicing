import sys

def http_hello_page(request, response):
    # Read the request line by line until we find the relevant data
    for line in request:
        if b'GET / HTTP/1.1' in line or b'POST / HTTP/1.1' in line:  # Simple check to ensure it's a valid request
            break
    
    # Assume username is sent as a query parameter `?username=`
    # We look for the 'username=' part and extract what follows
    start = line.find(b'?username=')
    if start != -1:
        start += len(b'?username=')
        end = line.find(b' ', start)  # Find end of URL (space after it)
        username_bytes = line[start:end]
        username = username_bytes.decode('utf-8')
        
        # Construct the response message
        message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}\r\n"
    else:
        # If no username was found, send a generic greeting
        message = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing username parameter.\r\n"

    # Write the response back to the client
    response.write(message.encode('utf-8'))