from flask import render_template,request
@app.route('/hello/<username>')
def hello(username):
   return render_template('hello.html', username=username)