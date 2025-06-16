from flask import Flask, request, render_template, url_for, redirect

app = Flask(__name__)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        return redirect(url_for('home'))
    else:
        return render_template("login.html")

@app.route('/')
def home():
    return "Welcome"
    
if __name__ == '__main__':
    app.run(debug=True)