from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        path = self.path.split('/')
        if len(path) > 1 and path[1]:
            username = path[1]
        else:
            username = "Guest"
        
        response_content = f"hello {username}"
        self.wfile.write(response_content.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()