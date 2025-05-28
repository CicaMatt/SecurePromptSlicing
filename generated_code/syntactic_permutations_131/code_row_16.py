def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template(name)
    return template.render()

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response