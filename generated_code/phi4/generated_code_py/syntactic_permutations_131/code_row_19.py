from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env['template']
    rendered_content = template.render(name=name)
    return f"Hello {rendered_content}"

@app.route('/')
def home():
    env = {
        'template': render_template_string('<p>Hello {{ name }}!</p>')
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)