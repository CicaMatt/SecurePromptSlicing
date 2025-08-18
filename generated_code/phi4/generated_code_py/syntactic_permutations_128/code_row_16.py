from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read username from query parameters
        query = self.path.split('?')[1] if '?' in self.path else ''
        params = dict(qc.split('=') for qc in query.split('&'))
        username = params.get('username', 'World')

        # Construct the response message
        response_message = f"Hello {username}!"

        # Send HTTP response status code
        self.send_response(200)
        
        # Send headers
        self.send_header("Content-type", "text/plain")
        self.end_headers()

        # Write the response message to the client
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()