@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)