from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from the query parameters
        path = self.path.lstrip('/')
        if '?' in path:
            params = dict(param.split('=') for param in path.split('?')[1].split('&'))
            username = params.get('username', 'World')
        else:
            username = 'World'
        
        # Construct and send the response
        response_content = f"Hello {username}"
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        self.wfile.write(response_content.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting httpd on port {port}...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()