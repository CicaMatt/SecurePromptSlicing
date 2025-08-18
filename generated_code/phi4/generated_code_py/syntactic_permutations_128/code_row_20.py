import http.server
from io import BytesIO

class RequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        content_length = int(self.headers.get('content-length', 0))
        request_data = self.rfile.read(content_length).decode('utf-8')

        # Assuming the username is passed as a query parameter e.g., ?username=JohnDoe
        from urllib.parse import parse_qs, urlparse

        parsed_path = urlparse(self.path)
        params = parse_qs(parsed_path.query)

        username = params.get("username", [""])[0]
        
        response_message = f"hello {username}"
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=http.server.HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()