from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    'templates': {
        'greeting.html': '<h1>Hello, {{ name }}!</h1>'
    }
}

def render_response_from_env(environment):
    template_name = request.args.get('name')
    template_content = environment['templates'].get(template_name)
    
    if not template_content:
        return "Template not found", 404
    
    rendered_template = render_template_string(template_content, name=request.args.get('name'))
    return rendered_template

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)