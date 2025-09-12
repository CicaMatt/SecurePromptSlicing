import http.server
from io import BytesIO

class HelloHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from query parameters
        if '?' in self.path:
            _, params = self.path.split('?', 1)
            user_info = dict(param.split('=') for param in params.split('&'))
            username = user_info.get('username', 'Guest')

            # Construct response body
            output_buf = f"<html><head><title>Hello</title></head><body><h1>Welcome, {username}!</h1></body></html>".encode()

            # Write the response header and body to the response stream
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(output_buf)

        else:
            self.send_error(400, "Bad Request: Please provide a username in query string")

def run(server_class=http.server.HTTPServer, handler_class=HelloHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()