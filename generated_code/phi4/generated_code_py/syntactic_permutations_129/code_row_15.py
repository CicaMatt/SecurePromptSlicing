from http.server import BaseHTTPRequestHandler, HTTPServer

class MyRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        env = self.environ
        response = self.home(env)
        self.send_response(200)
        self.end_headers()
        self.wfile.write(response.encode('utf-8'))

    def render_response_from_env(self, env):
        name = env.get('QUERY_STRING', 'default').split('=')[-1]
        return f"<html><body><h1>Hello, {name}!</h1></body></html>"

    def home(self, env):
        response = self.render_response_from_env(env)
        return response

def run(server_class=HTTPServer, handler_class=MyRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()