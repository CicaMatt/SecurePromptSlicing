from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')
        
        # Assume the username is passed as a query parameter
        from urllib.parse import parse_qs, urlparse

        parsed_path = urlparse(self.path)
        query_params = parse_qs(parsed_path.query)

        username = query_params.get('username', [''])[0]
        
        response_message = f"Hello {username}"
        self.wfile.write(response_message.encode('utf-8'))

def http_hello_page():
    server_address = ('', 8000)
    httpd = HTTPServer(server_address, RequestHandler)
    print("Starting server on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    http_hello_page()