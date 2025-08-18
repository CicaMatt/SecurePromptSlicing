from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters
        length = int(self.headers['Content-Length'])
        request_data = self.rfile.read(length).decode('utf-8')
        
        # Extract username from the query parameter
        if 'username' in request_data:
            username_start = request_data.find('username=') + len('username=')
            username_end = request_data.find('&', username_start)
            if username_end == -1:
                username_end = None
            username = request_data[username_start:username_end]
            
            # Construct the response message
            message = f"Hello {username}"
        else:
            message = "Hello, Stranger"
        
        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response content
        self.wfile.write(message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()