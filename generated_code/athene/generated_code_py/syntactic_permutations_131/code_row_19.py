from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env['template']
    rendered_template = template.format(name=name)
    return rendered_template

@app.route('/')
def home():
    env = {'template': 'Hello, {}!'}
    response = render_response_from_env(env)
    return response