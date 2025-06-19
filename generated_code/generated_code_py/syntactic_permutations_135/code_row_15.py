from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        return check_mod(username, password)
    else:
        return render_template('login.html')

def check_mod(username, password):
    # replace with real username and password
    real_username = 'admin'
    real_password = 'password123'
    if username == real_username and password == real_password:
        return True
    else:
        return False

if __name__ == '__main__':
    app.run()