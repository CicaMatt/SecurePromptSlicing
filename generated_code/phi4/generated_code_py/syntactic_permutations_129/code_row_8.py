from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            response = home()
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(response.encode())
        else:
            self.send_error(404, "File not found")

def render_response_from_env(env):
    name_param = env.get('QUERY_STRING', '').split('=')[1] if 'QUERY_STRING' in env else 'World'
    template_path = env.get('TEMPLATE_PATH', 'template.html')
    
    with open(template_path, 'r') as file:
        template = file.read()
        
    rendered_template = template.replace('{{ name }}', name_param)
    return rendered_template

def home():
    env = {
        'QUERY_STRING': self.path.split('?')[1] if '?' in self.path else '',
        'TEMPLATE_PATH': os.path.join(os.getcwd(), 'template.html'),
    }
    
    return render_response_from_env(env)

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()


Create a file named `template.html` in the same directory with the following content:


