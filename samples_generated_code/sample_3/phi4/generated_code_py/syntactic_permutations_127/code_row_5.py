from http.server import BaseHTTPRequestHandler, HTTPServer
import io

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        request_stream = self.rfile.read(int(self.headers['Content-Length']))
        request_data = request_stream.decode('utf-8')
        
        # Assuming the username is passed as a query parameter, e.g., ?username=John
        from urllib.parse import parse_qs, urlparse
        
        parsed_path = urlparse(self.path)
        query_params = parse_qs(parsed_path.query)
        username = query_params.get("username", [""])[0]
        
        response_content = f"Hello {username}"
        
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Using an in-memory BytesIO stream to simulate the file stream for the response
        response_stream = io.BytesIO(response_content.encode('utf-8'))
        self.wfile.write(response_stream.getvalue())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()