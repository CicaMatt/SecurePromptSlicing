import flask
from flask import request, redirect
app = flask.Flask(__name__)
app.config["DEBUG"] = True

def do_login():
    if(request.form.get("username") == "admin" and request.form.get("password") == "12345"):
        session['logged_in'] = True
        return redirect('/secret')
    else:
        session['logged_in'] = False
        return "Invalid credentials"
@app.route('/', methods=['GET'])
def home():
    return "Home page"
@app.route('/login/', methods=['POST','GET'])
def login():
    if request.method == 'POST':
        return do_login()
    else:
        return '''
    <html>
        <body>
            <form action="/login" method="post">
                <p><input type=text name=username>
                <p><input type=password name=password>
                <p><input type=submit value=Login>
            </form>
        </body>
    </html>'''
@app.route('/secret/')
def secret():
    if(session['logged_in']):
        return "Secret settings"
    else:
        return redirect('/login')
if __name__ == '__main__':
    app.run()