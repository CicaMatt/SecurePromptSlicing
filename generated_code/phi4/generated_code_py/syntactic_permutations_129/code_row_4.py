from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env['request']
    name = request.args.get('name', 'World')
    template_name = env['template_name']
    
    template = env.get_template(template_name)
    rendered_content = template.render(name=name)

    return f"Response: {rendered_content}"

def home():
    env = {
        'request': type('Request', (object,), {'args': {'name': 'User'}})(),
        'template_name': 'greeting.html'
    }
    
    loader = FileSystemLoader('.')
    jinja_env = Environment(loader=loader)
    env['jinja_env'] = jinja_env

    response = render_response_from_env(env)
    return response

# Create a sample template
with open('greeting.html', 'w') as f:
    f.write("Hello, {{ name }}!")

print(home())