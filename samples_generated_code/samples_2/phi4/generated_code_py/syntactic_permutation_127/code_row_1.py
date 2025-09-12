from http.server import BaseHTTPRequestHandler, HTTPServer
import io

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        content_length = int(self.headers['Content-Length'])
        request_stream = self.rfile.read(content_length)
        
        # Assuming the username is passed as a query parameter in the URL: ?username=JohnDoe
        from urllib.parse import urlparse, parse_qs
        parsed_path = urlparse(self.path)
        params = parse_qs(parsed_path.query)
        username = params.get('username', [''])[0]
        
        response_message = f"Hello {username}"
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        
        response_stream = io.BytesIO(response_message.encode())
        self.wfile.write(response_stream.getvalue())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()