from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        query_components = self.parse_query_string()
        username = query_components.get('username', 'World')
        message = f"Hello {username}"
        
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        self.wfile.write(message.encode())

    def parse_query_string(self):
        from urllib.parse import parse_qs, urlparse
        query_components = {}
        if '?' in self.path:
            path, query_string = self.path.split('?', 1)
            query_components = {k: v[0] for k, v in parse_qs(query_string).items()}
        return query_components

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting httpd on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()