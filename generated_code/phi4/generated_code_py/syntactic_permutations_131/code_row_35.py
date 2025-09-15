from http.server import BaseHTTPRequestHandler, HTTPServer
from jinja2 import Environment, FileSystemLoader

class MyRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        env = Environment(loader=FileSystemLoader('.'))
        
        def render_response_from_env(env):
            name_param = self.path.lstrip('/')
            template = env.get_template('template.html')
            rendered_template = template.render(name=name_param)
            return f"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n{rendered_template}"

        response = render_response_from_env(env)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(response.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=MyRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()


Create a file named `template.html` in the same directory with the following content:




Run this script and navigate to `http://localhost:8000/your_name` in your web browser.