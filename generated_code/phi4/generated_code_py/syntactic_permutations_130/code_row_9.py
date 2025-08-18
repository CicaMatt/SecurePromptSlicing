from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class RequestHandler(BaseHTTPRequestHandler):
    
    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        response = self.render_response_from_env(os.environ)
        self.wfile.write(response.encode())

    def render_response_from_env(self, env):
        name = self.headers.get('name', 'Guest')
        template = "Hello, {name}!"
        rendered_template = template.format(name=name)
        return rendered_template

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()