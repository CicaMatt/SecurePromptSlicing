from jinja2 import Environment, Template

def render_response_from_env(env):
    name = env['request'].get('name', 'World')
    template = Template('Hello, {{ name }}!')
    rendered_template = template.render(name=name)
    return rendered_template

def home():
    env = {'request': {'name': 'Alice'}}
    response = render_response_from_env(env)
    return response