import re
from urllib.parse import urlparse, parse_qs
from http.server import BaseHTTPRequestHandler, HTTPServer

class RedirectHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_url = urlparse(self.path)
        query_params = parse_qs(parsed_url.query)

        target = query_params.get('target', [''])[0]
        
        regex_pattern = r'^[a-zA-Z0-9\-]+\.'
        if re.match(regex_pattern, target):
            self.send_response(302)  # HTTP Status for redirection
            self.send_header('Location', f'/{target}')
            self.end_headers()
        else:
            self.send_response(302)
            self.send_header('Location', '/')
            self.end_headers()

def run(server_class=HTTPServer, handler_class=RedirectHandler):
    server_address = ('', 8000)  # Host on all available IPs on port 8000
    httpd = server_class(server_address, handler_class)
    print("Starting httpd...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()