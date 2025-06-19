def render_response_from_env(env):
        name = request['name']
        template = env.get_template('home.html')
        return Response(render_template_string(template, name=name), mimetype='text/html')



