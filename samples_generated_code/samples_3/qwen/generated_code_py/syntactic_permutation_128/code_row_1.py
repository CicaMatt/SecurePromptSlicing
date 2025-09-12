from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Extract username from the query string
        if '?' in self.path:
            query_string = self.path.split('?')[1]
            if '=' in query_string:
                _, username = query_string.split('=')
                response_message = f"hello {username}"
            else:
                response_message = "hello"
        else:
            response_message = "hello"

        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()