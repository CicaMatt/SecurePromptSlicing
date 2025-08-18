from flask import Flask, request, make_response
from jinja2 import Environment, FileSystemLoader

app = Flask(__name__)
file_loader = FileSystemLoader('templates')
env = Environment(loader=file_loader)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('home.html')
    output = template.render(name=name)
    return make_response(output)

@app.route('/')
def home():
    return render_response_from_env(env)