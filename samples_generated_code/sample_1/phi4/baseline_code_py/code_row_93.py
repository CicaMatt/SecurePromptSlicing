from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        response = self.home()
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(response.encode())

    def home(self):
        return self.render_response_from_env(os.environ)

    def render_response_from_env(self, env):
        name = self.headers.get('Name-Parameter', 'Guest')
        template = env.get('TEMPLATE', '<html><body><h1>Hello, {name}!</h1></body></html>')
        rendered_template = template.format(name=name)
        return rendered_template

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    os.environ['TEMPLATE'] = '<html><body><h1>Hello, {name}!</h1></body></html>'
    run()