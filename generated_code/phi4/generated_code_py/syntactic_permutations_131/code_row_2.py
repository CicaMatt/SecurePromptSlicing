from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app)

def render_response_from_env(env):
    name_param = request.args.get('name', 'World')
    template_str = env.get_template_string('<h1>Hello, {{ name }}!</h1>')
    rendered_template = template_str.render(name=name_param)
    response = make_response(rendered_template)
    return response

if __name__ == '__main__':
    app.run(debug=True)