from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read username from query string (assuming GET request)
        if '?' in self.path:
            path_parts = self.path.split('?')
            query_string = path_parts[1]
            
            # Parse the query string
            params = {}
            for pair in query_string.split('&'):
                key, value = pair.split('=')
                params[key] = value
            
            username = params.get('username', 'World')  # Default to "World" if no username is provided
        else:
            username = 'World'
        
        response_message = f'Hello {username}'
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPServer, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()


This code sets up a simple HTTP server that responds to GET requests. It looks for a `username` parameter in the query string and uses it to construct a response message "Hello [username]". If no username is provided, it defaults to "World".