from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Extract username from query string
        if '?' in self.path:
            _, params = self.path.split('?')
            param_pairs = [param.split('=') for param in params.split('&')]
            params_dict = {key: value for key, value in param_pairs}
            
            username = params_dict.get('username', 'World')
            response_message = f"hello {username}"
        else:
            response_message = "hello World"
        
        # Write the response
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPServer):
    server_address = ('', 8080)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8080...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()