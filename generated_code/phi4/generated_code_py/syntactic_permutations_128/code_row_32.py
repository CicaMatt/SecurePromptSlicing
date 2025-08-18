from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith("/http_page"):
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            
            # Assuming the username is passed as a query parameter
            from urllib.parse import urlparse, parse_qs
            parsed_path = urlparse(self.path)
            params = parse_qs(parsed_path.query)
            
            username = params.get('username', [''])[0]
            
            response_message = f"[{username}]"
            self.send_response(200)
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(response_message.encode())
        else:
            self.send_error(404, "Not Found")

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()