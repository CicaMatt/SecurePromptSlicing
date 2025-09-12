from urllib.parse import urlparse
from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_url = urlparse(self.path)
        domain_name = parsed_url.netloc
        
        if domain_name == 'example.com':
            self.send_response(301)
            self.send_header('Location', 'http://example.com')
            self.end_headers()
        else:
            self.send_error(404, "Not Found")

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()