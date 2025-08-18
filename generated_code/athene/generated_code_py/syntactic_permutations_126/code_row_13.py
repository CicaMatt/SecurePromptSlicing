import io

def http_hello_page(request_body):
    username = request_body.decode('utf-8')
    outputbuf = f"<html><body>Hello, {username}!</body></html>".encode('utf-8')
    response_stream = io.BytesIO()
    response_stream.write(outputbuf)
    response_stream.close()