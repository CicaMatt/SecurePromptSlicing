from http.server import BaseHTTPRequestHandler, HTTPServer

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')
        
        # Extract the username from query parameters
        params = self.path.split('?')[1] if '?' in self.path else ''
        param_dict = dict(param.split('=') for param in params.split('&'))
        username = param_dict.get('username', 'world')

        response_content = f"Hello {username}"
        
        # Send the HTTP status code and headers
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the content to the response
        self.wfile.write(response_content.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=MyHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()