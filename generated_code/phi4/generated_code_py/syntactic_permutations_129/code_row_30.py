from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env['template']
    rendered_template = template.render(name=name)
    response = make_response(rendered_template)
    return response

@app.route('/')
def home():
    env = {'template': render_template_string('<h1>Hello, {{ name }}!</h1>')}
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)