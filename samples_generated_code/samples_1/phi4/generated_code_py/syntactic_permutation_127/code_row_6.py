from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read the username from the query parameters
        if '?' in self.path:
            path_parts = self.path.split('?')
            query_params = path_parts[1]
            params = dict(qc.split('=') for qc in query_params.split('&'))
            username = params.get('username', 'World')

            response_message = f"Hello {username}"
        else:
            response_message = "Hello World"
        
        # Write the response to the output stream
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()