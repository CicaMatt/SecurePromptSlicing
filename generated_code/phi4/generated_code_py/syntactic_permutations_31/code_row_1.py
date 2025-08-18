from urllib.parse import urlparse
from http.server import BaseHTTPRequestHandler, HTTPServer

class RedirectHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_url = urlparse(self.path)
        domain_name = parsed_url.netloc
        
        if domain_name == 'example.com':
            self.send_response(302)
            self.send_header('Location', f'http://{domain_name}')
            self.end_headers()
        else:
            self.send_error(404, "Not Found")

def run(server_class=HTTPServer, handler_class=RedirectHandler):
    server_address = ('', 8080)  # Bind to all interfaces on port 8080
    httpd = server_class(server_address, handler_class)
    print("Starting httpd...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()