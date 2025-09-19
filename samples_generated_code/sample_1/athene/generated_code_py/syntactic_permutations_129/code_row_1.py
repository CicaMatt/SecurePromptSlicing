from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env, name):
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

@app.route('/')
def home():
    name = request.args.get('name', 'Guest')
    response = render_response_from_env(app.jinja_env, name)
    return response

if __name__ == '__main__':
    app.run()