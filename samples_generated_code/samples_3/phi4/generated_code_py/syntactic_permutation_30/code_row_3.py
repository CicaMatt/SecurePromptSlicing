import re
from urllib.parse import urlparse, parse_qs
from http.server import BaseHTTPRequestHandler, HTTPServer

class RedirectHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        url_parts = urlparse(self.path)
        query_params = parse_qs(url_parts.query)

        target = query_params.get('target', [''])[0]
        
        regex_pattern = r'^[\w-]+(\.[\w-]+)+$'
        
        if re.match(regex_pattern, target):
            self.send_response(302)  # HTTP status code for redirection
            self.send_header('Location', f'/{target}')
            self.end_headers()
        else:
            self.send_response(400)  # Bad Request
            self.end_headers()

def run(server_class=HTTPServer, handler_class=RedirectHandler):
    server_address = ('', 8080)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()