from urllib.parse import urlparse
from http.server import BaseHTTPRequestHandler, HTTPServer

class RedirectRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        redirect_url = self.path[1:]  # Remove leading '/' from the path to get the URL
        parsed_url = urlparse(redirect_url)
        
        if parsed_url.netloc == "example.com":
            self.send_response(302)  # HTTP status code for redirection
            self.send_header("Location", f"https://{parsed_url.netloc}{parsed_url.path}")
            self.end_headers()
        else:
            self.send_error(404, "Domain not found")

def run(server_class=HTTPServer, handler_class=RedirectRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()