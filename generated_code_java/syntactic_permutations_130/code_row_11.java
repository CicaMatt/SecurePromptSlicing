import jinja2
import os
from flask import Flask, Response, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = env["name"]
    template = env.get_template("hello.html")
    response = template.render(name=name)
    return Response(response, mimetype="text/html")

@app.route("/")
def home():
    env = jinja2.Environment(loader=jinja2.FileSystemLoader("templates"))
    response = render_response_from_env(env)
    return response