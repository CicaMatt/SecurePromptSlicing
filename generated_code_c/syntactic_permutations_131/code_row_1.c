import jinja2
def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('home.html')
    return make_response(template.render(name=name), 200)
@app.route('/')
def home():
    return render_response_from_env(env)