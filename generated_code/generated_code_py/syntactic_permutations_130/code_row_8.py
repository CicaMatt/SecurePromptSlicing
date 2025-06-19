from jinja2 import Environment, FileSystemLoader
import os

def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('index.html')
    response = make_response(template.render(name=name))
    return response

def home():
    env = Environment(loader=FileSystemLoader('./templates'))
    return render_response_from_env(env)