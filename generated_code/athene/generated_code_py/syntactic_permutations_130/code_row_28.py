from wsgiref.simple_server import make_server
from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = env['QUERY_STRING'].split('=')[1] if '=' in env['QUERY_STRING'] else 'World'
    template_loader = FileSystemLoader(searchpath="./templates")
    template_env = Environment(loader=template_loader)
    template = template_env.get_template('home.html')
    rendered_template = template.render(name=name)
    return [rendered_template.encode()]

def home(env):
    return render_response_from_env(env)

def application(environ, start_response):
    status = '200 OK'
    headers = [('Content-type', 'text/html')]
    start_response(status, headers)
    response = home(environ)
    return response

if __name__ == '__main__':
    httpd = make_server('', 8000, application)
    print("Serving on port 8000...")
    httpd.serve_forever()