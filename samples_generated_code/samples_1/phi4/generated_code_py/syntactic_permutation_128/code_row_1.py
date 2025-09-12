from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the request body
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')
        
        # Extract username from the request
        if 'username=' in post_data:
            username = post_data.split('username=')[1]
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            
            # Write response to the file stream
            response_message = f"hello {username}"
            self.wfile.write(response_message.encode('utf-8'))
        else:
            self.send_error(400, "Bad Request: username parameter missing")

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()