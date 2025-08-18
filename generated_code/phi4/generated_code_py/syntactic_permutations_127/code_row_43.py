from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        
        # Assuming that username is sent as a query parameter in the URL.
        from urllib.parse import parse_qs, urlparse
        parsed_path = urlparse(self.path)
        params = parse_qs(parsed_path.query)

        if 'username' in params:
            username = params['username'][0]
            response_message = f"Hello {username}"
            
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(response_message.encode())
        else:
            self.send_error(400, "Missing username query parameter")

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd server on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()