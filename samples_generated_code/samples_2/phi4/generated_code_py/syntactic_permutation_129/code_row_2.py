from flask import Flask, request, Response

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.jinja_loader.get_source(env, 'template.html')[0]
    rendered_template = env.jinja_env.from_string(template).render(name=name)
    return Response(rendered_template, mimetype='text/html')

if __name__ == '__main__':
    app.run(debug=True)