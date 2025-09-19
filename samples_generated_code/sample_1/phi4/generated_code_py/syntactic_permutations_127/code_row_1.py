from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameter for 'username'
        parsed_path = self.path.split('?')
        path = parsed_path[0]
        if len(parsed_path) > 1:
            params = parsed_path[1].split('=')
            if len(params) == 2 and params[0] == "username":
                username = params[1]
            else:
                username = "World"
        else:
            username = "World"

        # Construct the response
        message = f"Hello {username}"
        
        # Write the HTTP headers
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()