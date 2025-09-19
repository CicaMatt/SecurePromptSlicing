from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    name = request.args.get('name', 'World')
    
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    
    response = f"Content-Type: text/html\n\n{rendered_template}"
    return response

def home(env):
    return render_response_from_env(env)

# Example setup for demonstration purposes
env = Environment(loader=FileSystemLoader('.'))
env.request = type('Request', (object,), {'args': {'name': 'User'}})()

response = home(env)
print(response)