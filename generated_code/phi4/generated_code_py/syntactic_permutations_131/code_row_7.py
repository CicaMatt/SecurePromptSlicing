from flask import Flask, request

app = Flask(__name__)

env = {
    'home.html': '<h1>Welcome {{ name }}!</h1>',
}

def render_response_from_env():
    template_name = request.args.get('name')
    if not template_name:
        return "Name parameter is required", 400
    template = env.get(f'{template_name}.html')
    if not template:
        return f"Template for {template_name} not found", 404
    rendered_template = template.replace("{{ name }}", template_name)
    return rendered_template

@app.route('/')
def home():
    response = render_response_from_env()
    return response

if __name__ == '__main__':
    app.run(debug=True)