from http.server import BaseHTTPRequestHandler, HTTPServer

class MyHandler(BaseHTTPRequestHandler):
    def render_response_from_env(self, environ):
        # Get name parameter from request (query string)
        name = self.get_query_argument('name', 'Guest')

        # Get template from environment
        template = environ.get('TEMPLATE', '<h1>Hello {name}!</h1>')

        # Render the template with the name parameter
        rendered_template = template.format(name=name)

        return f"HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n{rendered_template}"

    def do_GET(self):
        env = {'TEMPLATE': '<h1>Hello {name}!</h1>'}
        response = self.render_response_from_env(env)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(response.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=MyHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()