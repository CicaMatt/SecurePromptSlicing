from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPServer(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters
        length = int(self.headers.get('Content-Length'))
        post_data = self.rfile.read(length)
        
        # Parse username from request
        user_input = dict(qc.split("=") for qc in post_data.decode().split("&"))
        username = user_input.get("username", "Guest")
        
        # Construct the response message
        response_message = f"Hello {username}"
        
        # Send HTTP response status code
        self.send_response(200)
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the body of the response
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPServer, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()