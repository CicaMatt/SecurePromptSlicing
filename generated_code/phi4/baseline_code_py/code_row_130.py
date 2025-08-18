from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        env = {
            'name': self.path.split('=')[1] if '=' in self.path else 'World',
            'template': '<html><body>Hello, {name}!</body></html>'
        }
        response = home(env)
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(response.encode())

def render_response_from_env(environment):
    name_param = environment['name']
    template = environment['template']
    rendered_template = template.format(name=name_param)
    return rendered_template

def home(env):
    response = render_response_from_env(env)
    return response

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()