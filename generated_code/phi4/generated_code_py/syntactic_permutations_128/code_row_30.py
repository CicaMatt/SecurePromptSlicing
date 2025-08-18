from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the request body from the client (if any)
        content_length = int(self.headers.get('Content-Length', 0))
        post_data = self.rfile.read(content_length) if content_length > 0 else b''
        
        # Extract username from POST data
        try:
            import urllib.parse as urlparse
            params = urlparse.parse_qs(post_data.decode('utf-8'))
            username = params.get('username', [''])[0]
        except Exception:
            username = ''
        
        # Construct the response message
        if username:
            response_message = f"Hello {username}"
        else:
            response_message = "Hello, what's your name?"
        
        # Write the response to the client
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(response_message.encode('utf-8'))

def http_hello_page(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8080)  # Serve on all available addresses on port 8080
    httpd = server_class(server_address, handler_class)
    print("Starting HTTP server...")
    httpd.serve_forever()

if __name__ == '__main__':
    http_hello_page()