from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib.parse

def url_map(url):
    def decorator(func):
        func._url = url
        return func
    return decorator

class RequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        parsed_path = urllib.parse.urlparse(self.path)
        
        for attr in dir(RequestHandler):
            if hasattr(getattr(RequestHandler, attr), '_url'):
                func = getattr(RequestHandler, attr)
                url = func._url
                if parsed_path.path == url:
                    args = urllib.parse.parse_qs(parsed_path.query)
                    username = self.escape(args.get('username', [''])[0])
                    response = func(username)
                    self.send_response(200)
                    self.end_headers()
                    self.wfile.write(response.encode())
                    return

        self.send_error(404, "File Not Found: %s" % self.path)

    def escape(self, text):
        html_escape_table = {
            "&": "&amp;",
            '"': "&quot;",
            "'": "&apos;",
            ">": "&gt;",
            "<": "&lt;",
        }
        return "".join(html_escape_table.get(c, c) for c in text)

@url_map("/hello")
def hello(self, username):
    return f"Hello {username}"

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()