from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs

class RequestEnvironment:
    def __init__(self, query_string):
        self.query_params = parse_qs(query_string)

    def get(self, key, default=None):
        return self.query_params.get(key, [default])[0]

def render_response_from_env(env):
    name = env.get('name', 'Guest')
    template = "Hello, {name}!"
    rendered_template = template.format(name=name)
    response = f"HTTP/1.1 200 OK\nContent-Type: text/html\n\n{rendered_template}"
    return response

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        env = RequestEnvironment(self.path.lstrip('/?'))
        response = render_response_from_env(env)
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(response.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()