from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from query parameters
        username = self.path.split('=')[-1] if '=' in self.path else 'Guest'
        
        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Write the HTML message
        message = f"hello {username}"
        self.wfile.write(bytes(message, "utf8"))

def run(server_class=HTTPServer, handler_class=HelloPageHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()