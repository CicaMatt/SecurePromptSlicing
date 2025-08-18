from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env, request):
    name = request.get('name', 'Guest')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home(env, request):
    response = render_response_from_env(env, request)
    return response

# Example usage
env = Environment(loader=FileSystemLoader('templates'))
request = {'name': 'John Doe'}
response = home(env, request)
print(response)