import http.server
from io import BytesIO

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        
        request_body = self.rfile.read(int(self.headers['Content-Length'])).decode('utf-8')
        username_start = request_body.find("username=") + len("username=")
        if username_start > len("username="):
            username_end = request_body.find("&", username_start)
            if username_end == -1:
                username_end = None
            username = request_body[username_start:username_end]
        else:
            username = "Guest"
        
        response_content = f"hello {username}".encode('utf-8')
        self.wfile.write(response_content)

def http_hello_page(server_class=http.server.HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    http_hello_page()