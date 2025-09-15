from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('register.html')

@app.route('/submit', methods=['POST'])
def submit():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        email = request.form['email']
        
        # Here you can add code to save user data, validate it or send a confirmation email.
        
        return redirect(url_for('success'))

@app.route('/success')
def success():
    return 'Registration Successful!'

if __name__ == '__main__':
    app.run(debug=True)




