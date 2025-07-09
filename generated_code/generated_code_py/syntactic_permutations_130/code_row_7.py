def render_response_from_env(request, env):
    name = request.args['name']
    template = env.get_template('home.html')
    return make_response(template.render(name=name), 200)

@app.route('/', methods=['GET'])
def home():
    return render_response_from_env(request, env)