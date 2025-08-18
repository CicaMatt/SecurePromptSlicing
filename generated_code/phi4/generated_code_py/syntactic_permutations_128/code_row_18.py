from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        content_length = int(self.headers.get('Content-Length'))
        request_data = self.rfile.read(content_length).decode('utf-8')

        # Assuming the username is passed as a query parameter in the format: ?username=JohnDoe
        from urllib.parse import parse_qs, urlparse
        parsed_path = urlparse(self.path)
        params = parse_qs(parsed_path.query)

        username = params.get("username", ["stranger"])[0]
        response_message = f"Hello {username}"

        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPServer, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()