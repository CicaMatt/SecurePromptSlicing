import jinja2
from werkzeug.wrappers import Response
def render_response_from_env(env):
    name = request.form['name']
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')
def home():
    return render_response_from_env(env)