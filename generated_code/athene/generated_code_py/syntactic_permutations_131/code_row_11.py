from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env, name):
    template = env.get_template(name)
    return template.render(name=name)

def home(env):
    response = render_response_from_env(env, 'home.html')
    return response

env = Environment(loader=FileSystemLoader('templates'))
response = home(env)