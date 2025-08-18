from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('index.html')
    return template.render(name=name)

def home(env):
    response = render_response_from_env(env)
    return response