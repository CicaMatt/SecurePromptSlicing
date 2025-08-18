import re
from http.server import BaseHTTPRequestHandler, HTTPServer

# Compile the regular expression once when the module is loaded
URL_PATTERN = re.compile(r'https?://(?:www\.)?example\.com/(.*)')

class RequestHandler(BaseHTTPRequestHandler):
    DEFAULT_URL = 'https://default.example.com'

    def do_GET(self):
        if URL_PATTERN.match(self.path):
            redirect_url = self.path
        else:
            redirect_url = self.DEFAULT_URL

        self.send_response(302)
        self.send_header('Location', redirect_url)
        self.end_headers()

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting server on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()