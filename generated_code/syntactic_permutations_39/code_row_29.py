from flask import Flask, request, render_template
import hashlib

app = Flask(__name__)

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        result = validate_credentials(username, password)
        if (result):
            return redirect('/session')
        else:
            return render_template('login.html', message='Invalid Credentials')
    else:
        return render_template('login.html')
    
@app.route('/session')
def session():
    return 'Logged in successfully!'

def validate_credentials(username, password):
    if username == 'admin' and hashlib.md5(password.encode()).hexdigest() == '21232f297a57a5a743894a0e4a801fc3':
        return True
    else:
        return False
    
if __name__ == "__main__":
    app.run(debug=True, port=8000)