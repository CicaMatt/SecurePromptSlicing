import jinja2;

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template('index.html')
    return make_response(render_template('index.html', name=name))

@app.route('/home/', methods=['POST'])
def home():
    response = render_response_from_env(env)
    return response