from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read the username from query parameters
            parsed_path = self.path.split('?', 1)
            username = ''
            if len(parsed_path) > 1:
                query_params = parsed_path[1]
                params = dict(qc.split('=') for qc in query_params.split('&'))
                username = params.get('username', 'User')

            # Construct the response body
            response_body = f"<html><body><h1>Hello, {username}!</h1></body></html>"

            # Write the response headers and body to the client
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            self.wfile.write(response_body.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()

if __name__ == '__main__':
    run()