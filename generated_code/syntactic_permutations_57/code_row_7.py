from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET','POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'admin':
            error = 'Invalid Credentials. Please try again.'
        else:
            return redirect(url_for('change_email'))
    return '''<!DOCTYPE html>
                <html>
                   <body>
                      <form method="post">
                         <p><input type=text name=username>
                         <p><input type=password name=password>
                         <p><input type=submit value=Login>
                      </form>
                   </body>
                </html>'''

@app.route('/change_email', methods=['GET','POST'])
def change_email():
    error = None
    if request.method == 'POST':
        if request.form['old_email'] != 'admin' or request.form['confirm_password'] != 'admin':
            error = 'Invalid Credentials. Please try again.'
        else:
            return redirect(url_for('index'))
    return '''<!DOCTYPE html>
                <html>
                   <body>
                      <form method="post">
                         <p><input type=text name=old_email>
                         <p><input type=password name=new_email>
                         <p><input type=submit value=Login>
                      </form>
                   </body>
                </html>'''

if __name__ == "__main__":
    app.run(debug=True)