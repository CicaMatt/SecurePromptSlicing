from jinja2 import Template
from flask import Flask, request, render_template

app = Flask(__name__)

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("template.html")
    rendered = template.render(name=name)
    response = Response(rendered)
    return response