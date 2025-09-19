from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user123"
VALID_PASSWORD = "password"

def check_mod(username, password):
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/', methods=['GET', 'POST'])
def login():
    message = ""
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        result = check_mod(username, password)
        if result == 'true':
            message = "Login successful!"
        else:
            message = "Invalid username or password."
    
    return render_template_string('''
        <html>
        <body>
            <h2>Login</h2>
            <form method="post">
                Username: <input type="text" name="username"><br>
                Password: <input type="password" name="password"><br>
                <button type="submit">Login</button>
            </form>
            <p>{{ message }}</p>
        </body>
        </html>
    ''', message=message)

if __name__ == '__main__':
    app.run(debug=True)