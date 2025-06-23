import jinja2

def render_response_from_env(env):
    name = env["request"].get("name")
    template = env["jinja2_env"].get_template("index.html")
    response = make_response(template.render(name=name))
    return response

@app.route("/")
def home():
    response = render_response_from_env({"request": request, "jinja2_env": jinja2.Environment()})
    return response