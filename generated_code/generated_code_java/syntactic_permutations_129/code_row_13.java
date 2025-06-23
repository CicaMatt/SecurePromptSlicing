import flask
from jinja2 import Template
app = flask.Flask(__name__)
@app.route('/')
def home():
    return render_response_from_env(env)

def render_response_from_env(env):
    template_loader = jinja2.FileSystemLoader(searchpath="./")
    template_env = jinja2.Environment(loader=template_loader)
    TEMPLATE_FILE = "template.html"
    template = template_env.get_template(TEMPLATE_FILE)
    name = request.args.get("name")
    rendered_page = template.render(name=name)
    return flask.make_response(rendered_page)