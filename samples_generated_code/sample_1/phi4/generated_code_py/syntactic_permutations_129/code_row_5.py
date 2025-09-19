from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.jinja_loader.get_source(env, 'home.html')[0]
    rendered_template = env.jinja_env.from_string(template).render(name=name)
    return f'<h1>Hello {name}!</h1>\n<p>{rendered_template}</p>'

if __name__ == '__main__':
    app.run(debug=True)