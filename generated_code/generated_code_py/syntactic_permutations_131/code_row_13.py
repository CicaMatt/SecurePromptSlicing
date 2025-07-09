from flask import Flask, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = env['request'].get('name')
    response = render_template(f'{name}.html', env=env)
    return response

@app.route('/')
def home():
    env = { 'variable': 'value'}
    response = render_response_from_env(env)
    return response