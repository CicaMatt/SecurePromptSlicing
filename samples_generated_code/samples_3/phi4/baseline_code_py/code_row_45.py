from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from the query string if present
        parsed_path = self.path.split('?', 1)
        base_path = parsed_path[0]
        
        username = "guest"
        if len(parsed_path) > 1:
            params = dict(qc.split("=") for qc in parsed_path[1].split("&"))
            username = params.get("username", "guest")

        # Create the response message
        response_message = f"Hello, {username}!"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the response body
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()