from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('response.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home():
    env = app.jinja_env
    response = render_response_from_env(env)
    return response

app.add_url_rule('/', 'home', home)

if __name__ == '__main__':
    app.run()