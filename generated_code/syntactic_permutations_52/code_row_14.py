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
The code generates a Flask application that defines three routes: /, /login, and /secret. The / route serves the index page with a link to the login page. 
The /login route is only accessible through POST requests, which check if the username and password are correct and then set the session['username'] variable accordingly. 
If the credentials are correct, it redirects to the secret page. If not, it returns an error message. The /secret route checks if the user has logged in by checking if the 'username' key is present in the session dictionary. 
If not, it renders the login page with a message. Otherwise, it displays the secret settings page.