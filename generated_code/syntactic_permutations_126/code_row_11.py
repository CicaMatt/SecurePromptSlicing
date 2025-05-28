import http.server
from io import BytesIO
class MyHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        message = "Hello, world!"
        self.wfile.write(message.encode())
        return

def http_hello_page():
    outputbuf = BytesIO()
    username = request.form['username']
    # ...
    response.stream.write(outputbuf.getvalue())
    response.stream.close()