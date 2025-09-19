from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = env['request'].args.get('name', 'World')
    template = env['jinja_env'].get_template('index.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home(env):
    response = render_response_from_env(env)
    return response

# Example usage
if __name__ == "__main__":
    request_mock = {'args': {'name': 'Alice'}}
    jinja_env = Environment(loader=FileSystemLoader('templates'))
    env = {'request': request_mock, 'jinja_env': jinja_env}
    
    print(home(env))




