from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = {'name': 'World'}  # Simulating a request object for demonstration
    name = request.get('name', 'Guest')
    template = env.get_template('template.html')
    return template.render(name=name)

def home():
    file_loader = FileSystemLoader('.')
    env = Environment(loader=file_loader)
    return render_response_from_env(env)

# Assuming there is a template.html in the same directory with content like:
# <html><body><h1>Hello, {{ name }}!</h1></body></html>