def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('hello.html')
    content = template.render(name=name)
    return Response(content, mimetype='text/html')

@app.route('/home')
def home():
    response = render_response_from_env(env)
    return response