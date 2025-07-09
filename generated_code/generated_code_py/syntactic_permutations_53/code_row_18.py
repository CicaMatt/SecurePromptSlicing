from flask import Flask, render_template, session

app = Flask(__name__)
app.secret_key = 'my_secret_key'

@app.route('/')
def index():
    if 'user' not in session:
        return redirect('login')
    if session['user'] == 'admin':
        return render_template('admin.html')
    else:
        return render_template('user.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # verify username and password here
        session['user'] = username
        return redirect(url_for('index'))
    else:
        return render_template('login.html')