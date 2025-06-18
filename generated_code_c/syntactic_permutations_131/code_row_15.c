import os
from flask import Flask, request, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    return make_response(template.render(name=name))

@app.route("/")
def home():
    return render_response_from_env(env)