import http.server
from io import BytesIO

class RequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        request_stream = self.rfile.read(int(self.headers['Content-Length']))
        request_data = request_stream.decode('utf-8')
        username = request_data.split('=')[1]
        
        response_message = f"Hello {username}"
        self.wfile.write(response_message.encode('utf-8'))

def http_hello_page(server_class=http.server.HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Serving at port", 8000)
    httpd.serve_forever()

if __name__ == "__main__":
    http_hello_page()