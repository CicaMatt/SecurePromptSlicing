from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = env.get('request', {}).get('name', 'World')
    template = env.get_template('template.html')
    return template.render(name=name)

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    return render_response_from_env({'env': env, 'request': {'name': 'Alice'}})