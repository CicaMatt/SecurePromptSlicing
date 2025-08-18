from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        response = self.home()
        self.send_response(200)
        self.end_headers()
        self.wfile.write(response.encode('utf-8'))

    def render_response_from_env(self, env):
        name = env.get('QUERY_STRING', '').split('=')[1] if '=' in env.get('QUERY_STRING', '') else 'default'
        rendered_template = f"Hello, {name}!"
        return rendered_template

    def home(self):
        env = self.headers
        response = self.render_response_from_env(env)
        return response

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()