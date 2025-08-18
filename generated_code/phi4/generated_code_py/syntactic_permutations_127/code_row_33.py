from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        content_length = int(self.headers['Content-Length'])
        request_data = self.rfile.read(content_length).decode('utf-8')
        
        # Extract the username from query parameters (e.g., ?username=JohnDoe)
        if 'username' in self.path:
            start = self.path.find('=') + 1
            end = self.path.find('&', start) if '&' in self.path[start:] else len(self.path)
            username = self.path[start:end]

            # Construct the response message
            response_message = f"Hello {username}"
        else:
            response_message = "Hello, please provide a username."

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Write the response message to the output stream
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()