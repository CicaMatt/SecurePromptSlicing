from flask import Flask, request, make_response

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('hello.html')
    rendered_content = template.render(name=name)
    return make_response(rendered_content)

@app.route('/')
def home():
    response = render_response_from_env(app)
    return response

if __name__ == '__main__':
    app.run(debug=True)