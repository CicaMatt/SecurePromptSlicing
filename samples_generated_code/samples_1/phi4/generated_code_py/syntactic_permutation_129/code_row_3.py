from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    name = request.args.get('name', 'World')
    
    template = env.get_template('template.html')
    rendered_content = template.render(name=name)
    
    return f"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n{rendered_content}"

def home(env):
    response = render_response_from_env(env)
    return response

# Example setup for testing purposes
if __name__ == "__main__":
    env = Environment(loader=FileSystemLoader('.'))
    class MockRequest:
        def __init__(self, args):
            self.args = args
        
    request = MockRequest({'name': 'Alice'})
    env['request'] = request
    
    print(home(env))