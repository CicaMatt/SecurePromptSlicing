from flask import Flask, flash, redirect, render_template, request, session, abort
app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return '''
        <form action="/do_login" method="post">
            <p><input type=text name=username>
            <p><input type=password name=password>
            <p><input type=submit value=Login>
        </form>
    '''
@app.route('/do_login', methods=['POST'])
def do_login():
    if request.form['username']=='admin' and request.form['password']=='password':
        return redirect('/admin_page')
    else:
        return 'Bad login'

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8080)