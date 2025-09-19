import re
from http.server import BaseHTTPRequestHandler, HTTPServer

# Compile regex once when module is loaded
url_pattern = re.compile(r'https?://(?:www\.)?example\.com/.*')

class RequestHandler(BaseHTTPRequestHandler):
    DEFAULT_URL = 'http://default.com'

    def do_GET(self):
        if url_pattern.match(self.path):
            redirect_url = self.path
        else:
            redirect_url = self.DEFAULT_URL

        self.send_response(302)
        self.send_header('Location', redirect_url)
        self.end_headers()

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()