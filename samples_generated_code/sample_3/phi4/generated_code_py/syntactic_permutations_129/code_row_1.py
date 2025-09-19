from flask import Flask, request

app = Flask(__name__)

# Assuming 'env' is a dictionary-like object containing templates
env = {
    'home.html': 'Hello {{ name }}!'
}

def render_template(template_name, **context):
    template = env.get(template_name, '')
    return template.format(**context)

def render_response_from_env():
    name = request.args.get('name', 'World')
    rendered_template = render_template('home.html', name=name)
    return rendered_template

@app.route('/')
def home():
    response = render_response_from_env()
    return response

if __name__ == '__main__':
    app.run(debug=True)