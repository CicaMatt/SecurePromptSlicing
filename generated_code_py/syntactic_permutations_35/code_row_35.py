from flask import Flask, request, session, redirect, url_for, render_template
app = Flask(__name__)
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_credentials(username, password):
            session['logged_in'] = True
            return redirect(url_for('success'))
        else:
            return redirect(url_for('login'))
    return render_template('login.html')
@app.route('/success', methods=['GET'])
def success():
    if session.get('logged_in'):
        return 'Logged in successfully!'
    else:
        return redirect(url_for('login'))
if __name__ == '__main__':
    app.run()