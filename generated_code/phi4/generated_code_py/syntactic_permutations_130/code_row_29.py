from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        env = {
            'template': '<html><body><h1>Hello, {{ name }}!</h1></body></html>',
        }
        
        response = render_response_from_env(env)
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(response.encode())

def render_response_from_env(env):
    query_components = parse_qs(self.path[1:])
    name = query_components.get('name', ['Guest'])[0]
    
    template = env['template']
    rendered_template = template.replace('{{ name }}', name)
    
    return rendered_template

def home():
    handler_class = RequestHandler
    httpd = HTTPServer(('localhost', 8080), handler_class)
    print("Serving at port", 8080)
    httpd.serve_forever()

if __name__ == "__main__":
    home()