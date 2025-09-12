from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read username from request path
        if self.path.startswith('/hello/'):
            username = self.path.split('/')[-1]
            if not username:
                self.send_error(400, "Bad Request: Username is required")
                return
            
            response_message = f"Hello {username}"
            
            # Send response status code
            self.send_response(200)
            # Set headers
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            
            # Write the message to the response body
            self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()