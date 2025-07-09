from flask import Flask, render_template, request, session
app = Flask(__name__)
@app.route('/info', methods=['GET'])
def info():
    if 'username' not in session or 'email' not in session or 'ssn' not in session:
        return 'Not authorized to access this page. Please login.'
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return render_template('info.html', username=username, email=email, ssn=ssn)
if __name__ == '__main__':
    app.run(debug=True)