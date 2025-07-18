from flask import *

app = Flask(__name__)

@app.route("/")
def main():
    return render_template('index.html')

@app.route("/login", methods=['POST', 'GET'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'admin':
            error = 'Invalid credentials'
        else:
            session['logged_in'] = True
            flash('You are logged in')
            return redirect(url_for('user'))
    return render_template('login.html', error=error)

@app.route("/user")
def user():
    if 'logged_in' not in session:
        flash('You are not logged in')
        return redirect(url_for('login'))
    else:
        return render_template('user.html')

@app.route("/admin")
def admin():
    if 'logged_in' not in session or 'username' not in session or request.form['username'] != 'admin':
        flash('You are not logged in as an admin')
        return redirect(url_for('login'))
    else:
        return render_template('admin.html')

@app.route("/logout")
def logout():
    session['logged_in'] = False
    flash('You are logged out')
    return redirect(url_for('login'))

if __name__ == "__main__":
    app.run(debug=True)