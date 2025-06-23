import urllib.parse as urllib
from http.server import HTTPServer, BaseHTTPRequestHandler
class RedirectHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_url = urllib.urlparse(self.path)
        if parsed_url.netloc == 'example.com':
            self.send_response(301)
            self.send_header('Location', '/')
            self.end_headers()
        else:
            self.send_error(404)