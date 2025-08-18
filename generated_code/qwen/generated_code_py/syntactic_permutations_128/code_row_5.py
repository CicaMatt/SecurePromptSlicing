from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from path, assuming format /?username=[username]
        username = self.path.split('=')[-1] if '=' in self.path else 'Guest'
        
        # Create response message
        response_message = f"hello {username}".encode('utf-8')
        
        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(response_message)

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()