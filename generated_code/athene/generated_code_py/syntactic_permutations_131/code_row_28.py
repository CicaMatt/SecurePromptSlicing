from jinja2 import Environment, FileSystemLoader
from http.server import BaseHTTPRequestHandler

def render_response_from_env(env: Environment, handler: BaseHTTPRequestHandler):
    name = handler.path.split('?')[1].split('=')[1] if '?' in handler.path else 'World'
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    handler.send_response(200)
    handler.send_header('Content-type', 'text/html')
    handler.end_headers()
    handler.wfile.write(rendered_template.encode('utf-8'))

def home(handler: BaseHTTPRequestHandler):
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    render_response_from_env(env, handler)