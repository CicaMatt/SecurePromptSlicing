from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.jinja_loader.get_source(env, 'template.html')[0]
    
    rendered_template = render_template_string(template, name=name)
    return rendered_template

# Example template for testing purposes
@app.route('/test-template')
def test_template():
    return '''
        <html>
            <body>
                <h1>Hello {{ name }}!</h1>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)