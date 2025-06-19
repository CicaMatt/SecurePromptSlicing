def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("hello.html")
    rendered = template.render(name=name)
    return Response(rendered, mimetype="text/html")

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response