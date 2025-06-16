import jinja2

def render_response_from_env(env):
    name = request.args["name"]
    template = env.get_template("index.html")
    return Response(rendered_template)

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response