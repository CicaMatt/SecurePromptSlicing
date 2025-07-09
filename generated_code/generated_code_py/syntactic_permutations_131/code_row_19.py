def render_response_from_env(env):
    name = request.args.get("name")
    return Response(render_template('index.html',name=name, env=env), mimetype='text/html')

@app.route('/')
def home():
    return render_response_from_env(env)