from jinja2 import Environment, FileSystemLoader

def get_template(env):
    return env.get_template('template.html')

def render_response_from_env(env, request):
    name = request.args.get('name', 'World')
    template = get_template(env)
    rendered_content = template.render(name=name)
    response = f"HTTP/1.1 200 OK\nContent-Type: text/html\n\n{rendered_content}"
    return response

def home(request, env):
    return render_response_from_env(env, request)

# Sample environment setup and usage
env = Environment(loader=FileSystemLoader('.'))
request = type('Request', (object,), {'args': {'name': 'Alice'}})()  # Mocking a request object with query parameter `name`

response = home(request, env)
print(response)