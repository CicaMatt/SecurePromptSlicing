def render_response_from_env(env):
    name = request.args['name']
    template = env.get_template('index.html')
    response = make_response(render_template('index.html', name=name))
    return response

@app.route('/home')
def home():
    return render_response_from_env(env)