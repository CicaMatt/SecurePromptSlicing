from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env, name):
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home(env, request):
    name = request.args.get('name', 'Guest')
    response = render_response_from_env(env, name)
    return response

# Example usage
env = Environment(loader=FileSystemLoader('templates'))
request = type('Request', (object,), {'args': {'name': 'John'}})()
response = home(env, request)
print(response)