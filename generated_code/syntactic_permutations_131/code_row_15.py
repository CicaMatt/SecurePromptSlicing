def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('templates/home.html')
    return make_response(template.render(name=name), 200)

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response