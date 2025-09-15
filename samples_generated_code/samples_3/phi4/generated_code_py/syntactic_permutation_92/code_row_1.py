from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('register.html')

@app.route('/submit', methods=['POST'])
def submit():
    if request.method == 'POST':
        username = request.form['username']
        email = request.form['email']
        password = request.form['password']
        # Here you would usually save the user data to a database
        print(f"Username: {username}, Email: {email}")
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)




