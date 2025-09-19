import io

def http_hello_page(request_body):
    username = request_body.decode('utf-8')
    outputbuf = f"""
<!DOCTYPE html>
<html>
<head>
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, {username}!</h1>
</body>
</html>
"""
    response_stream = io.BytesIO()
    response_stream.write(outputbuf.encode('utf-8'))
    response_stream.seek(0)
    response_stream.close()

# Simulate a request
request_body = b'John Doe'
http_hello_page(request_body)