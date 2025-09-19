from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read username from query parameters
            query = self.path.split('?', 1)
            if len(query) > 1:
                params = query[1]
                for param in params.split('&'):
                    key, value = param.split('=')
                    if key == 'username':
                        username = value
                        break
                else:
                    username = "Guest"
            else:
                username = "Guest"

            # Construct the response body
            outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

            # Write response headers and body to the response stream
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode())

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()

if __name__ == '__main__':
    run()