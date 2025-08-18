from http.server import BaseHTTPRequestHandler, HTTPServer

def http_hello_page(request: bytes) -> bytes:
    # Parse request headers
    lines = request.split(b'\r\n')
    method_line = lines[0].decode('utf-8').split()
    
    if len(method_line) < 2 or method_line[0] != 'GET':
        return b'HTTP/1.1 400 Bad Request\r\n\r\n'

    # Extract headers
    headers = {}
    for line in lines[1:]:
        if b':' in line:
            key, value = line.split(b':', 1)
            headers[key.decode('utf-8').strip()] = value.strip().decode('utf-8')
    
    # Check for 'username' parameter in the query string
    path = method_line[1]
    start = path.find('?') + 1 if '?' in path else None
    username = ''
    if start:
        query_params = path[start:].split('&')
        for param in query_params:
            key, value = param.split('=')
            if key == 'username':
                username = value
                break
    
    # Construct response
    greeting = f"Hello {username}" if username else "Hello"
    response_body = f"{greeting}".encode('utf-8')
    response_headers = (
        b'HTTP/1.1 200 OK\r\n'
        b'Content-Type: text/plain; charset=utf-8\r\n'
        b'Content-Length: ' + str(len(response_body)).encode('utf-8') + b'\r\n'
        b'\r\n'
    )
    response = response_headers + response_body
    return response

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read request body (not necessary for GET, but included for completeness)
        length = int(self.headers.get('Content-Length', 0))
        request = self.rfile.read(length) if length > 0 else b''
        
        # Generate response
        response_data = http_hello_page(request)
        
        # Send response status and headers
        self.send_response(200 if response_data.startswith(b'HTTP/1.1 200 OK') else 400)
        for header, value in zip(response_data.split(b'\r\n')[0].split(b': ')[1:], response_data.split(b'\r\n')[1:-2]):
            self.send_header(header.decode('utf-8'), value.decode('utf-8'))
        
        # End headers
        self.end_headers()
        
        # Write response body
        self.wfile.write(response_data.split(b'\r\n\r\n', 1)[1])

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd on port 8000...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()