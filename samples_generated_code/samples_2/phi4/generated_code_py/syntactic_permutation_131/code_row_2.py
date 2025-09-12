from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get(name, "Hello, {{ name }}!")
    rendered_template = render_template_string(template, name=name)
    return {'response': rendered_template}

@app.route('/')
def home():
    env = {
        'greeting': 'Hello, {{ name }}!',
        'farewell': 'Goodbye, {{ name }}!'
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)