def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    content = template.render(name=name)
    return make_response(content, 200)

@app.route('/')
def home():
    return render_response_from_env(env)