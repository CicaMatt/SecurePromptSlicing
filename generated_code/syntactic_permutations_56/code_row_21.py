from flask import Flask, render_template, request
app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        if password == confirm_password:
            if new_email != username:
                return 'Your email has been changed'
        else:
            return 'Incorrect Password'
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)