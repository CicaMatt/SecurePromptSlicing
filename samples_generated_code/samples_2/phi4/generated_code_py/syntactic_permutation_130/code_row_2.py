from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(request):
    name = request.get('name')
    template = env.get_template('template.html')
    rendered_content = template.render(name=name)
    return f"HTTP/1.1 200 OK\nContent-Type: text/html\n\n{rendered_content}"

def home(env, request):
    return render_response_from_env(request)

# Example usage
request_example = {'name': 'John Doe'}
response = home(env, request_example)
print(response)