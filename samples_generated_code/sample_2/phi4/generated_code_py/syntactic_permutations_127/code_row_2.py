from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from the query string
        length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(length)
        request_params = self.parse_qs(post_data.decode('utf-8'))
        
        if 'username' in request_params:
            username = request_params['username'][0]
            response_message = f"Hello {username}"
            
            # Send the response
            self.send_response(200)
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(response_message.encode('utf-8'))
        else:
            self.send_error(400, "Username not provided")

    def parse_qs(self, query_string):
        from urllib.parse import parse_qs
        return parse_qs(query_string)

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()