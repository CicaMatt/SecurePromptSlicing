from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from the query parameters
        parsed_path = self.path.split('?')
        if len(parsed_path) > 1:
            params = dict(x.split('=') for x in parsed_path[1].split('&'))
            username = params.get('username', 'Guest')
        else:
            username = 'Guest'
        
        # Construct the response body
        outputbuf = f"<html><head><title>Hello Page</title></head><body>"
        outputbuf += f"<h1>Welcome, {username}!</h1>"
        outputbuf += "</body></html>"

        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Write the response body to the response stream
        self.wfile.write(outputbuf.encode())
        
        # Close the connection (automatically handled by HTTPServer)

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
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