from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('greeting.html')
    rendered_template = template.render(name=name)
    return app.response_class(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    response = render_response_from_env(app.jinja_loader)
    return response

if __name__ == '__main__':
    app.run(debug=True)


