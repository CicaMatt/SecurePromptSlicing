from flask import Flask, render_template_string, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env['template']
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    env = {
        'template': render_template_string("<h1>Hello, {{ name }}!</h1>")
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)