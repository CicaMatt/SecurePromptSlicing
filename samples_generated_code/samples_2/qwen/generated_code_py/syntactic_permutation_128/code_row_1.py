from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        username = post_data.decode('utf-8').strip()

        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        response_message = f"hello {username}"
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()