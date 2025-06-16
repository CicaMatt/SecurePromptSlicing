from flask import Flask, request, make_response, render_template, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return 'Hello World!'
@app.route('/hello', methods=['POST'])
def hello():
    username = request.form['username']
    outputbuf = f'<html><body>Hello, {username}!</body></html>'
    response = make_response(outputbuf)
    return response
if __name__ == '__main__':
    app.run()