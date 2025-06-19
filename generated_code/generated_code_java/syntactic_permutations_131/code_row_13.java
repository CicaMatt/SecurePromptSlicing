import jinja2
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(env=jinja2)

def render_response_from_env(env):
    template_name = request.args.get('name')
    template = env.get_template(template_name)
    response = template.render()
    return response