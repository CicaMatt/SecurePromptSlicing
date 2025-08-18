from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

users = []

@app.route('/')
def index():
    return render_template('index.html', users=users)

@app.route('/add_user', methods=['POST'])
def add_user():
    username = request.form['username']
    users.append(username)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)