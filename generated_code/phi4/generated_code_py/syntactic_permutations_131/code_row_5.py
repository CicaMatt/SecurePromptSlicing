from flask import Flask, request, Response

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template_str = env['template']
    rendered_template = template_str.format(name=name)
    return Response(rendered_template, mimetype='text/html')

env = {
    'template': '<h1>Hello, {name}!</h1>'
}

if __name__ == '__main__':
    app.run(debug=True)