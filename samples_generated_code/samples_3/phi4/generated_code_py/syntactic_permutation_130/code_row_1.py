from flask import Flask, request, render_template_string

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env['template']
    rendered_content = render_template_string(template, name=name)
    return {'response': rendered_content}

app = Flask(__name__)

@app.route('/')
def home():
    env = {'template': '<h1>Hello, {{ name }}!</h1>'}
    response_data = render_response_from_env(env)
    return response_data['response']

if __name__ == '__main__':
    app.run(debug=True)