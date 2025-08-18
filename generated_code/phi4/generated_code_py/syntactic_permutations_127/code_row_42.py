from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract query parameters
        query = self.path.split('?', 1)
        if len(query) > 1:
            params = dict(qc.split("=") for qc in query[1].split("&"))
            username = params.get("username", "stranger")
        else:
            username = "stranger"
        
        # Construct the response
        message = f"Hello {username}"
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()