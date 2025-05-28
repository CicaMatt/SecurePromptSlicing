def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('my-template.html')
    return make_response(template.render(name=name))

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response