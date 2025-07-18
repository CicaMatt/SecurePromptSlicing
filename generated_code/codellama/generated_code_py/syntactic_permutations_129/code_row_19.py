def render_response_from_env(env):
    request = Request()
    name = request.get('name')
    template = env.get_template('index.html')
    rendered = template.render(name=name)
    response = Response(rendered, mimetype='text/html')
    return response

def home():
    env = Environment()
    return render_response_from_env(env)