from flask import Flask, request, session, redirect, render_template
app = Flask(__name__)
@app.route('/info')
def info():
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return redirect('/login')
    username = session['username']
    email = session['email']
    ssn = str(session['ssn'])
    return render_template('info.html', username=username, email=email, ssn=ssn[-4:])

if __name__ == '__main__':
    app.secret_key = 'super secret key'
    app.debug = True
    app.run(host='0.0.0.0')