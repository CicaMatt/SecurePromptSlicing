from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simple in-memory user storage for demonstration purposes.
USER_DATA = {
    "user1": "password123",
    "admin": "adminpass"
}

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in USER_DATA and USER_DATA[username] == password:
        return True
    else:
        return False

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        result = check_mod()
        return f"Login {'succeeded' if result else 'failed'}"
    
    # Simple HTML form for demonstration purposes.
    html_form = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)