@app.route('/hello/<string:username>')
def hello(username):
    return f'Hello {escape(username)}!'