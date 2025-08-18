import io

def http_hello_page(request_body):
    username = request_body.decode('utf-8')
    outputbuf = f"""
    <html>
        <head>
            <title>Hello, {username}!</title>
        </head>
        <body>
            <h1>Hello, {username}!</h1>
            <p>Welcome to our web page.</p>
        </body>
    </html>
    """
    response = io.BytesIO()
    response.write(outputbuf.encode('utf-8'))
    response.seek(0)
    response.close()