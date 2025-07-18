import jinja2

env = jinja2.Environment(loader=jinja2.FileSystemLoader('.'))

def render_response_from_env(env):
    template = env.get_template('index.html')
    name = request.args.get("name")
    rendered = template.render(name=name)
    return Response(rendered, content_type='text/html')

@app.route("/", methods=['GET'])
def home():
    response = render_response_from_env(env)
    return response