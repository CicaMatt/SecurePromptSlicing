from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    rendered_content = template.render(name=name)
    return rendered_content

@app.route('/')
def home():
    response = render_response_from_env(app.jinja_loader)
    return response

if __name__ == '__main__':
    app.run(debug=True)


