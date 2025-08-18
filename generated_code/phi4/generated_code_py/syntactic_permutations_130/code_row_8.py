from jinja2 import Environment, PackageLoader

def render_response_from_env(env):
    request = env['request']
    name = request.args.get('name', 'World')
    
    template = env.get_template('template.html')
    rendered_content = template.render(name=name)
    
    return f"HTTP/1.0 200 OK\nContent-Type: text/html; charset=utf-8\n\n{rendered_content}"

def home(env):
    response = render_response_from_env(env)
    return response

# Setup for demonstration purposes, usually you'd have a web server handle this
env = Environment(loader=PackageLoader('your_application', 'templates'))

# Example usage in a simple request handling scenario
class FakeRequest:
    def __init__(self, args):
        self.args = args

request = FakeRequest({'name': 'Alice'})
env['request'] = request

print(home(env))