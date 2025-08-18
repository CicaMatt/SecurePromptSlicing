from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read username from query parameters
        from urllib.parse import urlparse, parse_qs
        parsed_path = urlparse(self.path)
        query_components = parse_qs(parsed_path.query)
        username = query_components.get("username", [""])[0]
        
        # Construct response message
        response_message = f"Hello {username}"
        
        # Write the response to the client
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()


To test this code, you can start the server and access it via a web browser or `curl` with:

http://localhost:8080/?username=YourName