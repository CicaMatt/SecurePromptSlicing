from flask import Flask, render_template, request, redirect

app = Flask(__name__)

# Dummy data for demonstration purposes
users = {
    "admin": "password123"
}

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if users.get(username) == password:
        return redirect('/_page')
    else:
        return "Invalid credentials"

if __name__ == '__main__':
    app.run(debug=True)




