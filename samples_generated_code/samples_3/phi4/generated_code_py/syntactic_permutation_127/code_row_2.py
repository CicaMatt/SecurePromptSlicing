from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Read username from query parameters
        length = int(self.headers.get('content-length'))
        post_data = self.rfile.read(length).decode('utf-8')
        
        params = dict(qc.split("=") for qc in post_data.split("&") if qc)
        username = params.get('username', 'User')

        # Construct response message
        response_message = f"Hello {username}"

        # Write the response to the output stream
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()