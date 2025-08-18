from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from path
        if '?' in self.path:
            query = self.path.split('?')[1]
            if '=' in query:
                key, value = query.split('=')
                if key == 'username':
                    username = value
                else:
                    username = 'Guest'
            else:
                username = 'Guest'
        else:
            username = 'Guest'

        # Construct the response message
        response_message = f"Hello {username}"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the response body
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()