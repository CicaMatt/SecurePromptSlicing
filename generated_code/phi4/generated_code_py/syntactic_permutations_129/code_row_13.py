from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    'templates': {
        'home.html': '<h1>Welcome to {{ name }}!</h1>',
        # Add more templates as needed
    }
}

def render_response_from_env(environment):
    template_name = request.args.get('name', 'home') + '.html'
    template_content = environment['templates'].get(template_name, '')
    return render_template_string(template_content, name=request.args.get('name', 'Home'))

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)