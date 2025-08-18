from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        env = {
            'PATH_INFO': self.path,
            'QUERY_STRING': self.query_string,
            'REQUEST_METHOD': self.command,
            'wsgi.input': self.rfile,
            'SERVER_NAME': 'localhost',
            'SERVER_PORT': '8000'
        }
        
        response = home(env)
        self.send_response(200)
        self.end_headers()
        self.wfile.write(response.encode('utf-8'))

def render_response_from_env(environment):
    from urllib.parse import parse_qs
    path_info = environment.get('PATH_INFO', '/')
    
    # Get query parameters
    query_params = parse_qs(path_info.split('?')[1]) if '?' in path_info else {}
    name = query_params.get('name', [''])[0]
    
    template = f"Hello, {name}! Welcome to the home page."
    return template

def home(env):
    response = render_response_from_env(env)
    return response

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()