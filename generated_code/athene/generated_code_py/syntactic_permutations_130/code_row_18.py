from flask import request
from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env: Environment):
    name = request.args.get('name', 'World')
    template = env.get_template('response.html')
    return template.render(name=name)