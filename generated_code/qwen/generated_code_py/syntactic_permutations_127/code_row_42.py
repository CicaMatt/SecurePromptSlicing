from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from path or query parameters for simplicity, assuming /?name=JohnDoe
        from urllib.parse import urlparse, parse_qs
        parsed_path = urlparse(self.path)
        query_params = parse_qs(parsed_path.query)
        username = query_params.get('name', ['Guest'])[0]

        # Construct the response body
        response_body = f"Hello {username}".encode('utf-8')

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.send_header('Content-length', str(len(response_body)))
        self.end_headers()

        # Write the response body
        self.wfile.write(response_body)

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()