from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters from the URL
        parsed_path = self.path.split('?')
        if len(parsed_path) > 1:
            params = dict(x.split('=') for x in parsed_path[1].split('&'))
            username = params.get('username', 'World')
        else:
            username = 'World'
        
        # Construct the response message
        response_message = f"Hello {username}"
        
        # Send a 200 OK response
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response message to the output stream
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()