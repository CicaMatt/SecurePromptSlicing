from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters from the URL
        length = int(self.headers['Content-Length'])
        message_body = self.rfile.read(length)
        
        # Extract username from query parameters (assuming it's passed as a GET parameter)
        from urllib.parse import parse_qs, urlparse
        query_components = parse_qs(urlparse(self.path).query)
        username = query_components.get('username', ['stranger'])[0]

        # Construct the response message
        response_message = f"Hello {username}"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the response message to the output stream
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()