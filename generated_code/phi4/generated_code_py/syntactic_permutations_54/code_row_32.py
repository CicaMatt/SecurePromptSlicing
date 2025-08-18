from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/login', methods=['GET'])
def login():
    form_html = '''
    <form action="/do_login" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form> 
    '''
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in users_db and users_db[username] == password:
        return redirect('/_page')
    
    return "Invalid credentials. Please try again."

@app.route('/_page', methods=['GET'])
def protected_page():
    return "Welcome to the protected page!"

if __name__ == '__main__':
    app.run(debug=True)