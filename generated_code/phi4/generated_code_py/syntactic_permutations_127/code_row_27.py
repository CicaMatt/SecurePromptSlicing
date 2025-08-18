from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib.parse

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        query_components = urllib.parse.parse_qs(urllib.parse.urlparse(self.path).query)
        username = query_components.get('username', [''])[0]
        if not username:
            self.send_response(400)
            self.end_headers()
            self.wfile.write(b"Bad Request: No username provided.")
            return
        
        response_message = f"Hello {username}"
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting httpd on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()