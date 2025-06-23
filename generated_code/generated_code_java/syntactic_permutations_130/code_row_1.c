import os
from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
def home():
    return render_response_from_env(env)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("template.html")
    rendered = template.render(name=name)
    response = make_response(rendered)
    return response