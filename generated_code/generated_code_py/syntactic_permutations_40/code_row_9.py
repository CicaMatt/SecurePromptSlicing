from flask import Flask, render_template, request, url_for, redirect
app = Flask(__name__)
@app.route("/info", methods=['GET'])
def info():
    session['username'] = 'admin'
    session['email'] = 'abc@xyz.com'
    session['ssn'] = 123456789
    return render_template('info.html', username = session['username'], email=session['email'], ssn = str(session['ssn'])[:4])
if __name__ == '__main__':
    app.run()