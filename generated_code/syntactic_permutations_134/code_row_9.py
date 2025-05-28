@app.route('/hello/<username>')
def hello(username):
    return 'Hello {}'.format(escape(username))