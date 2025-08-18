from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env: Environment):
    request = {'args': {'name': 'John Doe'}}  # Mock user request
    name = request['args']['name']
    template = env.get_template('template.html')
    rendered_response = template.render(name=name)
    return rendered_response