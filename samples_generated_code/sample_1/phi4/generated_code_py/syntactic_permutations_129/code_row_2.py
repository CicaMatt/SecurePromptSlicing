from flask import Flask, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    request = env['flask.request']
    name = request.args.get('name', 'World')
    template = env['flask.template_name_or_list'][0]
    
    rendered_content = render_template_string(template, name=name)
    return f"<html><body>{rendered_content}</body></html>"

@app.route('/')
def home():
    env = {
        'flask.request': app.test_request_context().request,
        'flask.template_name_or_list': ['<h1>Hello, {{ name }}!</h1>']
    }
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)