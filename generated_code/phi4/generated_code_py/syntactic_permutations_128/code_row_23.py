import http.server
from io import BytesIO

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        content_length = int(self.headers.get('content-length', 0))
        request_data = self.rfile.read(content_length)

        username_start = b'username='
        if username_start in request_data:
            start_index = request_data.index(username_start) + len(username_start)
            end_index = request_data[start_index:].index(b'&')
            username = request_data[start_index:start_index+end_index].decode()

            response_message = f"hello {username}"
            self.wfile.write(response_message.encode())

if __name__ == '__main__':
    httpd = http.server.HTTPServer(('localhost', 8000), SimpleHTTPRequestHandler)
    print("Serving at port", 8000)
    httpd.serve_forever()