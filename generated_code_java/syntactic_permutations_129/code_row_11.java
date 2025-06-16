import jinja2

def render_response_from_env(env):
    template = env.get_template('name')
    name = request.args['name']
    response = make_response(render_template(template, name=name))
    return response

@app.route('/')
def home():
    return render_response_from_env(env)