def http_hello_page(server, request):
    import cgi
    inputbuf = request.read()
    outputbuf = ""
    outputbuf += """<!DOCTYPE html>
    <html>
      <head><title>Hello Page</title></head>
      <body>
        <h1>Hello, World!</h1>
        <p>""" + cgi.escape(inputbuf) + """</p>
      </body>
    </html>
    """
    request.send_response(200)
    request.send_header('Content-type', 'text/html')
    request.end_headers()
    request.wfile.write(outputbuf)