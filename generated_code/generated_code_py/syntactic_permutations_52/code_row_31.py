from flask import Flask, render_template, request, redirect, session  #import flask library
app = Flask(__name__)                                                #creates an instance of the class flask

@app.route("/")                                                      #decorator that is used to map the function to a url
def index():
    return render_template("index.html")

@app.route("/login", methods=["POST"])
def do_login():
    if request.form['username'] == 'admin' and request.form['password'] == 'secret':
        session['logged_in'] = True
        return redirect("/secret")
    else:
        return render_template("login-error.html")

@app.route("/secret")
def secret():
    if not session.get('logged_in'):
        return "Please log in first"
    else:
        return render_template("secret.html")

if __name__ == "__main__":
    app.run(debug=True, port=5000)