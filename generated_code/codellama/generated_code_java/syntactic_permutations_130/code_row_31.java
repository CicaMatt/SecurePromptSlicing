import jinja2
from jinja2 import Environment, FileSystemLoader
def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    return make_response(template.render(name=name))
@app.route("/", methods=["GET"])
def home():
    render_response_from_env(env)