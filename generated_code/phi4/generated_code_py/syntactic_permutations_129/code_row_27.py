from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get('template', '')
    rendered_template = render_template_string(template, name=name)
    return f"<h1>{rendered_template}</h1>"

@app.route('/home')
def home():
    env = {
        'template': "Hello, {{ name }}!"
    }
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)