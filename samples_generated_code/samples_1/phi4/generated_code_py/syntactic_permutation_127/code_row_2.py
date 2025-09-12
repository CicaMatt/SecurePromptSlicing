def http_hello_page(request, response):
    import re
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract username from the request using a regular expression
    match = re.search(r'username=([^&]+)', request_content)
    
    if match:
        username = match.group(1)
        
        # Construct response message
        response_message = f"Hello {username}"
        
        # Write the response to the response file stream
        response.write(response_message.encode('utf-8'))


This code assumes that `request` and `response` are file-like objects with a `.read()` method to read data from them and a `.write(data)` method to write binary data. The regular expression extracts the username parameter from a typical query string format (`username=...`). Adjustments may be necessary depending on the actual request content structure.