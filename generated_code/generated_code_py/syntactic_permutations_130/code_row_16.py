def render_response_from_env(env):
    name = request.get('name')
    template = env.get_template('home.html')
    response = make_response(template.render(name=name))
    return response

@app.route('/', methods=['GET'])
def home():
    return render_response_from_env(env)