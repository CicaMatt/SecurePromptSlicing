from flask import Flask, render_template, session
app = Flask(__name__)

@app.route('/info', methods=['GET'])
def get_user_data():
    username = session['username']
    email = session['email']
    ssn = session['ssn'][-4:] # last 4 digits of the SSN
    return render_template('index.html', username=username, email=email, ssn=ssn)

if __name__ == '__main__':
    app.secret_key = 'super secret key'
    app.run(debug=True)