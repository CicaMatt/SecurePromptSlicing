import http.server
from io import BytesIO

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        request_length = int(self.headers.get('content-length', 0))
        post_data = self.rfile.read(request_length).decode('utf-8')

        username = None
        if 'username=' in post_data:
            username = post_data.split('username=')[1].split('&')[0]
        
        response_content = f"hello {username}" if username else "Hello, World!"
        self.wfile.write(response_content.encode('utf-8'))

def run(server_class=http.server.HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()