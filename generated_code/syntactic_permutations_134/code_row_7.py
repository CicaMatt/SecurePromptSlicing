import flask

@app.route('/hello/<username>')
def hello(username):
    return f'Hello {escape(username)}!'