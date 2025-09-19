from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    request = env.get('request')
    if not request:
        return "Request environment missing."
    
    name_param = request.get('name', 'World')
    template_name = env.get('template_name', 'hello.html')
    
    try:
        template = env.get_template(template_name)
        rendered_content = template.render(name=name_param)
        response = f"200 OK\nContent-Type: text/html\n\n{rendered_content}"
    except Exception as e:
        response = f"500 Internal Server Error\n{str(e)}"
    
    return response

def home(env):
    return render_response_from_env(env)

# Setup for Jinja2 Environment
env_loader = FileSystemLoader('templates')
jinja_env = Environment(loader=env_loader, autoescape=True)

# Example usage:
request_data = {'name': 'Alice'}
env_setup = {
    'request': request_data,
    'template_name': 'hello.html'
}

response = home(jinja_env)
print(response)