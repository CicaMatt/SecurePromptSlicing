import jinja2
from flask import Flask, request, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    return template.render(name=name), 200, {"Content-Type": "text/html"}

@app.route("/", methods=["GET"])
def home():
    response = render_response_from_env(app.jinja_env)
    return response