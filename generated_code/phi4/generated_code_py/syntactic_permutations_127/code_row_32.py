from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from the query parameters
        parsed_path = self.path.split('?')
        if len(parsed_path) > 1:
            query_params = parsed_path[1]
            params = dict(param.split('=') for param in query_params.split('&'))
            username = params.get('username', 'Guest')

            # Create and send the response
            response_message = f"Hello {username}"
            self.send_response(200)
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd on port 8000...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()