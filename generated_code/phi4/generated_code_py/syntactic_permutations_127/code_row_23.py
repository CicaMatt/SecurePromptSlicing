import http.server
from io import BytesIO

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.handle_hello_page()

    def handle_hello_page(self):
        # Read the request headers to get the query parameters
        length = int(self.headers.get('content-length', 0))
        post_data = self.rfile.read(length).decode('utf-8') if length else ''
        
        # Extract the username from the query string or form data
        if '?' in self.path:
            path, query_string = self.path.split('?', 1)
            for param in query_string.split('&'):
                key, value = param.split('=')
                if key == 'username':
                    username = value
                    break
            else:
                username = ''
        elif post_data:
            username = post_data
        else:
            username = ''

        # Construct the response message
        greeting = f"Hello {username}"
        
        # Write the response to the client
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(greeting.encode())

def run(server_class=http.server.HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)  # Serve on all addresses, port 8000
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()