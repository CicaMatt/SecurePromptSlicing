from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env.get('request', {})
    name = request.get('name', 'Guest')
    
    template_name = env.get('template', 'index.html')
    template = env.loader.get_template(template_name)
    
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}"

def home(env):
    response = render_response_from_env(env)
    return response

# Setup environment
file_loader = FileSystemLoader(searchpath="./templates")
env = Environment(loader=file_loader)

# Example usage:
env['request'] = {'name': 'Alice'}
response = home(env)
print(response)  # This will print the rendered template response with name Alice