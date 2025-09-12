from http.server import BaseHTTPRequestHandler, HTTPServer
import io

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        content_length = int(self.headers.get('Content-Length', 0))
        request_body = self.rfile.read(content_length) if content_length else b''
        
        request_stream = io.BytesIO(request_body)
        response_stream = io.BytesIO()
        
        # Parse the request for username
        self.path = self.path.lstrip('/')
        if self.command == 'GET' and '?' in self.path:
            path, query_string = self.path.split('?', 1)
            params = dict(qc.split('=') for qc in query_string.split('&'))
            username = params.get('username', 'World')
            
            # Create response
            response_content = f"hello {username}"
            response_stream.write(response_content.encode())
        
        # Send the HTTP response back to client
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        self.wfile.write(response_stream.getvalue())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()