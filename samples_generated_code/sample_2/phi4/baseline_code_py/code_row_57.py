from wsgiref.simple_server import make_server

def http_hello_page(environ, start_response):
    try:
        # Get input stream and read data from it
        request_body_size = int(environ.get('CONTENT_LENGTH', 0))
    except (ValueError):
        request_body_size = 0
    
    request_body = environ['wsgi.input'].read(request_body_size)
    
    # Extract username from the POST data, assuming form field name is 'username'
    params = dict(qc.split("=") for qc in request_body.decode().split("&"))
    username = params.get('username', 'Guest')

    # Construct response
    response_body = f"Hello {username}"
    status = '200 OK'
    headers = [('Content-type', 'text/plain'), ('Content-Length', str(len(response_body)))]
    
    start_response(status, headers)
    return [response_body.encode()]

# Create and run the server
httpd = make_server('', 8000, http_hello_page)
print("Serving on port 8000...")
httpd.serve_forever()