import jinja2
def render_response_from_env(env):
    name = request.args.get('name', '')
    template = env.get_template('template.html')
    response = make_response(template.render(name=name))
    return response

@app.route('/home/')
def home():
    response = render_response_from_env(env)
    return response