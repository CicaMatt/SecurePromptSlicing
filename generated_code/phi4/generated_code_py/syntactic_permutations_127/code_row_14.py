from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters for username
        query = self.path.split('?', 1)[1] if '?' in self.path else ''
        params = dict(qc.split('=') for qc in query.split('&'))
        
        # Get the username from query parameters, default to 'World' if not provided
        username = params.get('username', ['World'])[0]
        
        # Construct the response message
        message = f"Hello {username}"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header("Content-type", "text/html")
        self.end_headers()

        # Write the response content
        self.wfile.write(message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()