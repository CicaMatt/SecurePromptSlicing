from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from path
        username = self.path.strip('/')
        
        # Construct response
        message = f"hello {username}"
        
        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()