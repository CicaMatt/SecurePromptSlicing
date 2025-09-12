from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Extract username from the query string
        username = self.path.split('=')[1] if '=' in self.path else 'Guest'
        
        # Construct the response message
        response_message = f"Hello {username}"
        
        # Write the response to the response file stream
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloPageHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()