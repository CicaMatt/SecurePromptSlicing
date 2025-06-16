java
import jinja2

def render_response_from_env(env):
    name = request.args('name')
    template = env.get_template('hello.html')
    return template.render(name=name)

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response