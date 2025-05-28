def render_response_from_env(env):
    request = env['request']
    name = request.args['name'].first()
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')
def home():
    env = globals()
    response = render_response_from_env(env)
    return response