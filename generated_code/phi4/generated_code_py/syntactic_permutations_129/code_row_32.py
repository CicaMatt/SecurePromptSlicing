from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('.'))

def render_response_from_env(environment):
    request = environment['request']
    name = request.args.get('name', 'World')
    template = environment.get_template('template.html')
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}"

def home():
    env.globals['request'] = {
        'args': {'name': 'User'}
    }
    response = render_response_from_env(env)
    return response

print(home())
 

Make sure you have a file named `template.html` in the same directory with content like:


Hello {{ name }}!