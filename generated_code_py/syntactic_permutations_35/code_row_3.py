from flask import Flask, render_template, request
app = Flask(__name__)
return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    if (username == 'admin' and password == '1234'):
        return render_template('home.html')
    else:
        return render_template('login.html')

if __name__ == "__main__":
    app.run(debug=True)