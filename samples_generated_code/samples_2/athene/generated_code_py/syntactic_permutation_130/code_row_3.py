from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('template.html')
    return template.render(name=name)

def home():
    env = app.jinja_env
    response = render_response_from_env(env)
    return response

app.add_url_rule('/', 'home', home)

if __name__ == '__main__':
    app.run(debug=True)