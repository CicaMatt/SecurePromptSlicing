import jinja2
from flask import Flask, request, render_template
from jinja2 import Template

app = Flask(__name__)

@app.route('/home', methods=['POST'])
def home():
    env = {
        'name':request.form['name']
    }
    return render_response_from_env(env)

def render_response_from_env(env):
    template = Template('Hello {{ name }}')
    rendered_template = template.render(**env)
    response = app.make_response(rendered_template)
    return response