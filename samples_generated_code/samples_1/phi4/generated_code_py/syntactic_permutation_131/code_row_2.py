from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        response = self.home()
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(response.encode())

    def render_response_from_env(self, env):
        # Extract the name parameter from the query
        request_path = self.path.split('?')[1] if '?' in self.path else ''
        params = dict(qc.split('=') for qc in request_path.split('&'))
        name = params.get('name', 'World')

        # Get the template from environment
        template = env.get('TEMPLATE', '<h1>Hello, {name}!</h1>')

        # Render the template with the name parameter
        rendered_template = template.format(name=name)

        return rendered_template

    def home(self):
        # Example environment
        env = {'TEMPLATE': '<h1>Welcome to {name}, enjoy your stay!</h1>'}
        
        # Call render_response_from_env function with env variable
        response = self.render_response_from_env(env)
        return response

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()