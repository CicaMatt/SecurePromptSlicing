from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = env.get('request', {}).get('name', 'World')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response