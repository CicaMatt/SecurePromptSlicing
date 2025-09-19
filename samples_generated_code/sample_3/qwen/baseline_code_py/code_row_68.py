from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from path, assuming format /?username=<username>
        if '?' in self.path:
            query = self.path.split('?')[1]
            params = dict(qc.split('=') for qc in query.split('&'))
            username = params.get('username', 'Guest')
        else:
            username = 'Guest'

        # Construct the response
        message = f"hello {username}"
        
        # Write response
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()