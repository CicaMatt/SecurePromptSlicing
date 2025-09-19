from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        content_length = int(self.headers['Content-Length'])
        request_data = self.rfile.read(content_length).decode('utf-8')

        if 'username=' in request_data:
            username_start = request_data.find('username=') + len('username=')
            username_end = request_data.find('&', username_start)
            username = request_data[username_start:username_end] if username_end != -1 else request_data[username_start:]
            greeting_message = f"Hello {username}"
        else:
            greeting_message = "Hello Stranger"

        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(greeting_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()