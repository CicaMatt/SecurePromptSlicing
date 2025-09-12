from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        content_length = int(self.headers.get('Content-Length', 0))
        request_body = self.rfile.read(content_length).decode('utf-8')

        username_start = request_body.find("username=") + len("username=")
        if username_start < len("username="):
            username = "Guest"
        else:
            username_end = request_body.find("&", username_start)
            if username_end == -1:
                username_end = None
            username = request_body[username_start:username_end]

        message = f"Hello, {username}!"
        
        self.wfile.write(message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()