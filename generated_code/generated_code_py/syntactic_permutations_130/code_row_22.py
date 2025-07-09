def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('template.html')
    return response(template.render(name=name))

home = lambda env, request: render_response_from_env(env)