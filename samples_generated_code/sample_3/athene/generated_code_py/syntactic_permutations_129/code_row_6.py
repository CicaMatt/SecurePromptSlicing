from flask import Flask, request, render_template

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', '')
    rendered_template = render_template(env['template_name'], name=name)
    return app.response_class(rendered_template, content_type='text/html')

@app.route('/')
def home():
    env = {'template_name': 'home.html'}
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)