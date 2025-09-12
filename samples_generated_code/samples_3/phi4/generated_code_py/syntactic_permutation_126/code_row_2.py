import http.server
import socketserver

class MyHttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            content_length = int(self.headers['Content-Length'])
            username = self.rfile.read(content_length).decode('utf-8')
            
            outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"
            
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))
        else:
            super().do_GET()

def run(server_class=http.server.HTTPServer, handler_class=MyHttpRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Server started at localhost:8000")
    httpd.serve_forever()

if __name__ == "__main__":
    run()