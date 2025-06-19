import os
from flask import Flask, render_template
from jinja2 import Environment, FileSystemLoader
app = Flask(__name__)
env = Environment(loader=FileSystemLoader('templates'))
@app.route('/')
def home():
    template = env.get_template('index.html')
    return render_response_from_env(env)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')
if __name__ == '__main__':
    app.run()