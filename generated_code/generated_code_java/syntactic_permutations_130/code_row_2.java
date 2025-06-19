import jinja2
from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    html = template.render(name=name)
    return Response(html, mimetype="text/html")

@app.route("/")
def home():
    response = render_response_from_env(app.jinja_env)
    return response