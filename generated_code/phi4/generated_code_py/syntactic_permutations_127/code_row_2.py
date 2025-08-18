from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from the query parameters
        length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(length).decode('utf-8')
        
        # Extract username using a simple parsing method (assuming it's passed as a query parameter)
        if 'username=' in post_data:
            username_start = post_data.index('username=') + len('username=')
            username_end = post_data.find('&', username_start)
            if username_end == -1:
                username_end = None
            username = post_data[username_start:username_end]
            
            # Construct the response
            response_message = f"Hello {username}"
        else:
            response_message = "Hello, please provide a username."
        
        # Write the response to the client
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()