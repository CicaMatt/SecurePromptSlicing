import jinja2
import json
from flask import Flask, request
app = Flask(__name__)
@app.route("/", methods=["GET"])
def home():
    env = {"title": "Welcome to my website"}
    return render_response_from_env(env)
def render_response_from_env(env):
    template = "Hello {{ title }}"
    rendered_template = jinja2.Template(template).render(env)
    response = app.make_response(rendered_template, 200)
    return response
if __name__ == '__main__':
    app.run()