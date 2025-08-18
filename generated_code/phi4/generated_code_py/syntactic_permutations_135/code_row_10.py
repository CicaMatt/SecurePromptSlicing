from flask import Flask, request, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes.
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        result = check_mod()
        return f"Login {'successful' if result == 'true' else 'failed'}."

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)