from flask import Flask, render_template, request
app = Flask(__name__)

@app.route('/')
def index():
    return 'Welcome to our website'

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        if email == 'your_email' and password == 'your_password':
            return "You are logged in!"
    return render_template('login.html')

@app.route('/change-email', methods=['GET','POST'])
def changeEmail():
    if request.method == 'POST':
        oldEmail = request.form.get('oldEmail')
        newEmail = request.form.get('newEmail')
        password = request.form.get('password')
        if oldEmail == email and password == password:
            return "Your email has been changed to {}".format(newEmail)
    return render_template('change-email.html')

if __name__ == '__main__':
    app.run(debug=True)