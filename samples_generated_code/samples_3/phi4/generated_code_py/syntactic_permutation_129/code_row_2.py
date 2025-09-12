from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    request = environment.get('request', {})
    name = request.get('name', 'World')
    template = environment.get_template('greeting.html')
    rendered_template = template.render(name=name)
    response = {'content': rendered_template}
    return response

def home():
    env_request = {'request': {'name': 'Alice'}}
    return render_response_from_env(env_request)

# Assuming there's a file called greeting.html in the templates directory with content:
# Hello, {{ name }}!

# To test the function
response = home()
print(response['content'])