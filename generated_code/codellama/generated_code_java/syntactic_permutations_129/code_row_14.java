import jinja2;

def render_response_from_env(env):
    name = request.args('name')
    template = env.get_template(name)
    return Response(template.render(), mimetype='text/html')

@app.route('/', methods=['GET'])
def home():
    return render_response_from_env(env)