from jinja2 import Environment, Template

def render_response_from_env(env):
    name = 'World'  # Assuming a default name for demonstration purposes
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return f"<html>{rendered_template}</html>"

def home():
    env = Environment(loader=jinja2.FileSystemLoader('templates'))
    response = render_response_from_env(env)
    return response