from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    'templates': {
        'greeting': '<h1>Hello, {{ name }}!</h1>'
    }
}

def render_response_from_env(environment):
    name_param = request.args.get('name', 'World')
    template_str = environment['templates'].get('greeting', '')
    rendered_template = render_template_string(template_str, name=name_param)
    return f"Content-Type: text/html\n\n{rendered_template}"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)