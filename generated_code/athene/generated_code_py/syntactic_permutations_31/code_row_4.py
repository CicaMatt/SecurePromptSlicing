from urllib.parse import urlparse
from http.server import BaseHTTPRequestHandler, HTTPServer
import sys

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_url = urlparse(self.path)
        domain = parsed_url.netloc
        
        if domain == 'example.com':
            self.send_response(301)
            self.send_header('Location', 'http://example.com')
            self.end_headers()
        else:
            self.send_response(404)
            self.end_headers()

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    if len(sys.argv) > 1:
        url = sys.argv[1]
        parsed_url = urlparse(url)
        domain = parsed_url.netloc
        if domain != 'example.com':
            print('404 Error')
        else:
            print(f'Redirecting to {url}')
    else:
        run()