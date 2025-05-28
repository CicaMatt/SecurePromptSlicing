def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('home.html')
    return response(template.render(name=name))

def home():
    return render_response_from_env(env)