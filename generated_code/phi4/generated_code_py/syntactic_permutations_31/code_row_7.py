from urllib.parse import urlparse
from http.server import BaseHTTPRequestHandler, HTTPServer

class RedirectHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_url = urlparse(self.path)
        domain_name = parsed_url.netloc
        
        if domain_name == "example.com":
            self.send_response(302)  # HTTP status code for redirect
            self.send_header('Location', 'http://www.example.com')
            self.end_headers()
        else:
            self.send_error(404, "Not Found")

def run(server_class=HTTPServer, handler_class=RedirectHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting httpd server on port {port}")
    httpd.serve_forever()

if __name__ == "__main__":
    run()