from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = env['request'].args.get('name', 'World')
    template = env.get_template('home.html')
    rendered_content = template.render(name=name)
    return rendered_content

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response