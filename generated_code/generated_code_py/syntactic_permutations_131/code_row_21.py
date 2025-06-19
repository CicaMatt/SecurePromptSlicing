import jinja2
def render_response_from_env(env):
    name = request.args("name")
    template = env.get_template("index.html")
    response = make_response(template.render(name=name))
    return response
@app.route("/")
def home():
    return render_response_from_env(env)