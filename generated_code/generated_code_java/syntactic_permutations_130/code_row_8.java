import jinja2  # import Jinja templating library
from flask import Flask, request, render_template, Response  # import Flask, request and render_template functions for Flask

app = Flask(__name__)  # create a Flask app object
env = Environment(loader=FileSystemLoader('templates'))  # create a Jinja environment to load templates from the "templates" directory

def render_response_from_env(env):
    name = request.args.get('name')  # get 'name' parameter from the request
    template = env.get_template('index.html')  # get a Jinja template named "index.html" from the environment
    rendered_template = template.render(name=name)  # render the template with the 'name' parameter
    return Response(rendered_template, mimetype='text/html')  # create a Flask response object with the rendered template and an HTML mime type

@app.route('/')  # map the home function to the root URL of the app
def home():
    response = render_response_from_env(env)  # call the render_response_from_env function with the environment
    return response  # return the rendered template in an HTTP response object