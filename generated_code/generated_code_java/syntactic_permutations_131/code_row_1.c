import jinja2;
from flask import Flask, render_template;

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    content = template.render(name=name)
    return Response(content, mimetype="text/html")

app = Flask(__name__)
env = jinja2.Environment(loader=PackageLoader("app", "templates"))

@app.route("/")
def home():
    return render_response_from_env(env)