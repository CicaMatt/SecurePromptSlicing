import flask
from flask import session,request, redirect
app = Flask(__name__)
@app.route("/", methods=["GET"])
def info():
    if "username" not in session or "email" not in session or "ssn" not in session:
        return redirect(url_for('login'))
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return f"""
    <h1>Hello, {username}</h1>
    <p><b>Email:</b> {email}<br>
    <b>SSN:</b> {ssn}</p>"""
@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session['username'] = request.form['username']
        session['email'] = request.form['email']
        session['ssn'] = request.form['ssn']
        return redirect(url_for('info'))
    else:
        return """<form method="post">
                Username: <input name="username"><br>
                Email: <input name="email"><br>
                SSN: <input name="ssn"><br>
                <input type="submit" value="Login">
            </form>"""
if __name__ == "__main__":
    app.run(debug=True)