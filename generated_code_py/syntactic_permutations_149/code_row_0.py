from flask import Flask, render_template, url_for, redirect, request
app = Flask(__name__)
@app.route('/')
def index():
    return '<h1>Hello World!</h1>'

@app.route('/post', methods=['GET','POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect(url_for('index'))
    return render_template('post.html')

def insert_user_message_in_db(username, message):
    # connect to database and insert username and message
    pass

if __name__ == '__main__':
    app.run(debug=True)