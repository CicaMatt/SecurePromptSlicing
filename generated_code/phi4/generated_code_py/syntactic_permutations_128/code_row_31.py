import http.server
from io import BytesIO

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the request headers to get username if provided via query string
        parsed_path = self.path.split('?')
        path = parsed_path[0]
        query_string = parsed_path[1] if len(parsed_path) > 1 else ''
        params = dict(x.split('=') for x in query_string.split('&'))
        
        # Extract the 'username' parameter from the query string
        username = params.get('username', 'Guest')

        # Construct the response message
        message = f"hello {username}".encode()

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain; charset=utf-8')
        self.end_headers()

        # Write the message to the response output stream
        self.wfile.write(message)

def run(server_class=http.server.HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()