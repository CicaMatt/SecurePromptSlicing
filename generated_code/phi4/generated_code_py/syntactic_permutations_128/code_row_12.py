from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Extracting the username from query parameters
        query = self.path.split('?')[1] if '?' in self.path else ''
        params = dict(qc.split('=') for qc in query.split('&'))
        username = params.get('username', 'Guest')

        # Constructing response message
        response_message = f"hello {username}"
        
        # Writing the response to the file stream
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()