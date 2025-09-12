from http.server import BaseHTTPRequestHandler, HTTPServer

def http_hello_page(request: BaseHTTPRequestHandler) -> None:
    request_length = int(request.headers['Content-Length'])
    post_data = request.rfile.read(request_length).decode('utf-8')
    
    # Assuming the username is passed as a query parameter 'username'
    from urllib.parse import parse_qs, urlparse
    parsed_path = urlparse(request.path)
    params = parse_qs(parsed_path.query)

    username = params.get("username", [""])[0]

    response_message = f"Hello {username}"
    
    request.send_response(200)
    request.send_header('Content-type', 'text/html')
    request.end_headers()
    request.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=BaseHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, lambda *args: http_hello_page(*args))
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()