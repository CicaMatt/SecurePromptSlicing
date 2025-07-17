def http_hello_page(environ, start_response):
    # Read in the request body 
    request_body_size = int(environ.get('CONTENT_LENGTH', 0))
    username = environ['wsgi.input'].read(request_body_size).decode()

    outputbuf = "<html>\n" + \
                    "  <head>\n" + \
                        "    <title>Hello</title>\n" + \<s>                     "</head>\n" + \
                    "  <body>\n" + \
                        "    <h1>Hello, {username}!</h1>\n" + \
                    "</html>"

    # Start the response
    status = '200 OK'
    response_headers = [('Content-Type', 'text/html')]
    start_response(status, response_headers)
    
    return [outputbuf.encode()]