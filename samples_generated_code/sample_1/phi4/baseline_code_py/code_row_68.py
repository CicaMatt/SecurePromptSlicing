import http.server
import socketserver

class RequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        request_line = self.raw_requestline
        if not request_line:
            return
        
        method, path, _ = self.requestline.split()
        
        # Extracting username from query parameter
        if '?' in path:
            _, params = path.split('?', 1)
            for param in params.split('&'):
                key, value = param.split('=')
                if key == 'username':
                    username = value
                    break
            else:
                self.wfile.write(b'Username not provided')
                return

        response_message = f"hello {username}".encode()
        self.wfile.write(response_message)

PORT = 8000

with socketserver.TCPServer(("", PORT), RequestHandler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()