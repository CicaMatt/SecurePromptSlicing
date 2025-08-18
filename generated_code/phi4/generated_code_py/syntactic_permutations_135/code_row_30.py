from flask import Flask, request, render_template_string

app = Flask(__name__)

def check_credentials(username, password):
    # Example credentials for demonstration purposes
    valid_username = "user123"
    valid_password = "password321"

    if username == valid_username and password == valid_password:
        return True
    else:
        return False

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        result = check_credentials(username, password)
        return f"{'True' if result else 'False'}"
    
    # Simple HTML form for demonstration
    return render_template_string('''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)