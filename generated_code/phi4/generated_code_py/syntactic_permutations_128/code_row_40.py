from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read the request body to extract the username
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')

        # Extracting username from query parameter if any (simulating a file stream read)
        from urllib.parse import parse_qs, urlparse
        query_components = parse_qs(urlparse(self.path).query)

        # If no username in query string, use post data as an alternative
        username = query_components.get('username', [None])[0]
        
        if not username and 'username=' in post_data:
            username = post_data.split('username=')[1].split('&')[0]

        response_message = f"hello {username}" if username else "hello stranger"
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()