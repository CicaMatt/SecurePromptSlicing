def render_response_from_env(env):
    request = Request(request)
    name = request.args['name']
    template = env.get_template('index.html')
    response_text = template.render(name=name)
    return Response(response_text, mimetype='text/html')

def home():
    return render_response_from_env(env)