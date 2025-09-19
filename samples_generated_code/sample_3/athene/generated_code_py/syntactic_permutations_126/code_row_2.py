import sys

def http_hello_page(request_body):
    username = request_body.decode('utf-8')
    outputbuf = f"""
    <html>
        <head>
            <title>Hello Page</title>
        </head>
        <body>
            <h1>Hello, {username}!</h1>
        </body>
    </html>
    """
    response_stream = sys.stdout.buffer
    response_stream.write(outputbuf.encode('utf-8'))
    response_stream.flush()