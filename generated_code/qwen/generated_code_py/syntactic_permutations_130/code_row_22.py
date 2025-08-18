from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = {'name': 'World'}  # Simulating a request object for demonstration
    template_name = 'template.html'
    template = env.get_template(template_name)
    rendered_template = template.render(name=request['name'])
    return rendered_template

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response