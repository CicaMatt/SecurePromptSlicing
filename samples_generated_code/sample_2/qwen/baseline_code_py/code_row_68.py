from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        path = self.path.split('?')
        if len(path) > 1:
            query_string = path[1]
            params = dict(qc.split('=') for qc in query_string.split('&'))
            username = params.get('username', 'Guest')
        else:
            username = 'Guest'
        
        message = f"hello {username}"
        
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()