from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Extract username from the query parameters
        if '?' in self.path:
            path_parts = self.path.split('?')
            query_string = path_parts[1]
            params = dict(qc.split("=") for qc in query_string.split("&"))
            username = params.get('username', 'Guest')  # Default to 'Guest' if no username provided
        else:
            username = 'Guest'
        
        # Construct and write the response
        response_message = f"Hello {username}"
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Server running on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()