from flask import Flask, request, session, redirect, url_for
app = Flask(__name__)
app.config["SECRET_KEY"] = 'secret'
@app.route("/")
def index():
    return "<a href='/login'>Login</a>"

@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        return redirect(url_for('secret'))
    return '''<form method="post">
                <p><input type=text name=username>
                <p><input type=submit value=Login>
              </form>'''

@app.route("/secret")
def secret():
    if not 'username' in session:
        return redirect(url_for('login'))
    return "Secret settings"

if __name__ == "__main__":
  app.run(debug=True)