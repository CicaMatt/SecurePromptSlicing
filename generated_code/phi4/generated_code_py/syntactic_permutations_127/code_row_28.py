from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read username from the query string
        parsed_path = self.path.split('?')
        if len(parsed_path) > 1:
            params = dict(param.split('=') for param in parsed_path[1].split('&'))
            username = params.get('username', 'World')
        else:
            username = 'World'
        
        # Construct the response
        greeting = f"Hello {username}"
        
        # Write the response to the client
        self.wfile.write(greeting.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting httpd on port {port}...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()