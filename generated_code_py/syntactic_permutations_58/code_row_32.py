from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def login():
    # check if the email and password are correct
    if request.form['email'] == 'admin@example.com' and request.form['password'] == '123456':
        return redirect('/dashboard')
    else:
        return redirect('/login-error')

@app.route('/change-email', methods=['POST'])
def change_email():
    # check if the user is logged in and their old email and password are correct
    if request.form['old_email'] == 'admin@example.com' and request.form['password'] == '123456':
        return redirect('/dashboard')
    else:
        return redirect('/login-error')

if __name__ == "__main__":
    app.run(debug=True)