import os
from flask import Flask, request, redirect, url_for
from jinja2 import Environment, FileSystemLoader

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args['name']
    template = env.get_template(name + '.html')
    return template.render()

@app.route('/home/')
def home():
    env = Environment(loader=FileSystemLoader('.'))
    response = render_response_from_env(env)
    return response