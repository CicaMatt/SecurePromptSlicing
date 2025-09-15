from jinja2 import Environment, select_autoescape

def render_response_from_env(env):
    request = {'name': 'World'}  # Simulating a request object with a name parameter
    template = env.get_template('template.html')
    rendered_template = template.render(name=request['name'])
    return rendered_template

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader, autoescape=select_autoescape())
    response = render_response_from_env(env)
    return response

# Simulating a simple file system loader for demonstration purposes
from jinja2 import FileSystemLoader

if __name__ == "__main__":
    print(home())


template.html

