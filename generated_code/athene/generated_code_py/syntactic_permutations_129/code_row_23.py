from flask import request, Flask
from jinja2 import Environment, FileSystemLoader

app = Flask(__name__)
file_loader = FileSystemLoader('templates')
env = Environment(loader=file_loader)

def render_response_from_env(env):
    name = request.args.get('name', 'default_name')
    template = env.get_template('template.html')
    return template.render(name=name)