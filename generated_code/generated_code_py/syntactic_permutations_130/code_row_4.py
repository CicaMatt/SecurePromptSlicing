def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template('index.html')
    return Response(template.render(name=name), mimetype='text/html')

@app.route('/home')
def home():
    return render_response_from_env(env)