from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    'templates': {
        'home.html': '<h1>Hello {{ name }}</h1>'
    }
}

def render_response_from_env(environment):
    template_name = request.args.get('name', 'default')
    template_str = environment['templates'].get(f'{template_name}.html', '')
    rendered_template = render_template_string(template_str, name=request.args.get('name', 'World'))
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)