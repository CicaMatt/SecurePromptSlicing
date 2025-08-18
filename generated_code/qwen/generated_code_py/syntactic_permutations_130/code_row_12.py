from jinja2 import Environment, select_autoescape

def render_response_from_env(env):
    name = env.get('name', 'World')
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader, autoescape=select_autoescape(['html', 'xml']))
    response = render_response_from_env(env)
    return response