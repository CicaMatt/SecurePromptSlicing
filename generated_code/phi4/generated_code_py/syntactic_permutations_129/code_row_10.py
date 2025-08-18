from flask import Flask, render_template_string

app = Flask(__name__)

env = {
    'template': '<h1>Welcome to {{ title }}!</h1>',
    'context': {'title': 'My Web App'}
}

def render_response_from_env(environment):
    template = environment['template']
    context = environment.get('context', {})
    rendered_template = render_template_string(template, **context)
    response = f"<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>Rendered Template</title></head><body>{rendered_template}</body></html>"
    return response

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)