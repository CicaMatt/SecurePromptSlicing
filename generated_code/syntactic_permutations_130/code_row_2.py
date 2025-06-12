def render_response_from_env(env):
        name = request.args['name']
        template = env.get_template('mytemplate.html')
        rendered = template.render(name=name)
        return Response(rendered, mimetype='text/html')

