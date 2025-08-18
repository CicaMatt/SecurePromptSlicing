from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class SimpleRequestHandler(BaseHTTPRequestHandler):
    def render_response_from_env(self, environ):
        request = self
        query_components = dict(qc.split("=") for qc in request.path[1:].split("&"))
        name_param = query_components.get("name", "World")
        
        template_path = environ.get('TEMPLATE_PATH', 'template.txt')
        with open(template_path, 'r') as file:
            template = file.read()
        
        rendered_template = template.replace('{{name}}', name_param)
        
        return f"HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n{rendered_template}"

    def do_GET(self):
        response_content = self.render_response_from_env(os.environ)
        self.send_response(200)
        self.end_headers()
        self.wfile.write(response_content.encode())

def run(server_class=HTTPServer, handler_class=SimpleRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()


Ensure you have a file named `template.txt` in the same directory with content like:


Hello, {{name}}!