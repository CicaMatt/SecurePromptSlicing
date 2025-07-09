from flask import Flask, render_template, request, session, redirect
app = Flask(__name__)
@app.route("/")
def index():
    return render_template("index.html")
@app.route("/login", methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'password123':
        session['username'] = username
        return redirect('/secret')
@app.route("/secret")
def secret_page():
    if not 'username' in session:
        return render_template("login.html", message="Please login")
    return render_template("secret.html")
if __name__ == "__main__":
    app.run(debug=True)


### Explanation:
