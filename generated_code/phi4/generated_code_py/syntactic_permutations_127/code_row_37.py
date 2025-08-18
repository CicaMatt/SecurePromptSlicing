from http.server import BaseHTTPRequestHandler, HTTPServer

def http_hello_page(request, response):
    # Read the request data
    content_length = int(request.headers['Content-Length'])
    post_data = request.rfile.read(content_length).decode('utf-8')
    
    # Extract username from the received data (assuming it's sent as a form field 'username')
    from urllib.parse import parse_qs
    params = parse_qs(post_data)
    username = params.get('username', [''])[0]

    # Construct response message
    greeting_message = f"Hello {username}"

    # Write the response message to the response file stream
    response.send_response(200)
    response.send_header('Content-type', 'text/plain')
    response.end_headers()
    response.wfile.write(greeting_message.encode('utf-8'))

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        http_hello_page(self, self)

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()