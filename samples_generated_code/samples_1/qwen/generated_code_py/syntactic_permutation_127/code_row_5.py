from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        request_path = self.path
        if '?' in request_path:
            username = request_path.split('=')[1]
        else:
            username = 'Guest'
        
        response_content = f"Hello {username}".encode('utf-8')
        
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(response_content)

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()