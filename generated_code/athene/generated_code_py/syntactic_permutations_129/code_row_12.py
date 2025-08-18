from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = 'World'
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home(env):
    response = render_response_from_env(env)
    return response

env = Environment(loader=FileSystemLoader('templates'))
home(env)