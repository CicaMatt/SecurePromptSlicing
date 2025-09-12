from jinja2 import Environment, Template

def render_response_from_env(env):
    request = env['request']
    name = request.args.get('name', 'World')
    template_str = env['template']
    template = Template(template_str)
    rendered_template = template.render(name=name)
    response = f"Content-Type: text/html\n\n{rendered_template}"
    return response

def home(env):
    return render_response_from_env(env)

# Simulated environment for demonstration
env = {
    'request': {
        'args': {'name': 'Alice'}
    },
    'template': '<html><body>Hello, {{ name }}!</body></html>'
}

# Example usage:
response = home(env)
print(response)