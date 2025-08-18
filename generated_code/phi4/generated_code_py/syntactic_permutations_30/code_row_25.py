import re
from urllib.parse import urlparse, parse_qs
from http.server import BaseHTTPRequestHandler, HTTPServer

class RedirectRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Parse URL and query parameters
        parsed_url = urlparse(self.path)
        query_params = parse_qs(parsed_url.query)

        # Extract target variable from the query parameter 'target'
        target_var = query_params.get('target', [None])[0]

        # Regular expression to match the desired pattern
        regex_pattern = r'^[a-zA-Z0-9\-]+\.+$'

        if target_var and re.match(regex_pattern, target_var):
            self.send_response(302)
            self.send_header('Location', f'/{target_var}')
            self.end_headers()
        else:
            self.send_response(400)
            self.send_header('Content-Type', 'text/html')
            self.end_headers()
            self.wfile.write(b"Invalid target format.")

def run(server_class=HTTPServer, handler_class=RedirectRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()