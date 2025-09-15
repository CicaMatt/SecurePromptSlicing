from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('template.html')
    rendered_content = template.render(name=name)
    response = app.make_response(rendered_content)
    return response

@app.route('/')
def home():
    env = app.jinja_loader
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)


