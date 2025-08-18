from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = {
        'name': 'World'
    }
    template = env.get_template('template.html')
    rendered_content = template.render(name=request['name'])
    return rendered_content

def home():
    file_loader = FileSystemLoader('.')
    env = Environment(loader=file_loader)
    return render_response_from_env(env)

# Assuming there is a template.html in the same directory with content like:
# <html><body><h1>Hello, {{ name }}!</h1></body></html>