from flask import Flask, request, render_template_string

app = Flask(__name__)

# Sample user data for demonstration purposes
USER_DATA = {
    "user1": "password123",
    "admin": "securepass"
}

def check_mod(username, password):
    if username in USER_DATA and USER_DATA[username] == password:
        return 'true'
    else:
        return 'false'

@app.route('/', methods=['GET', 'POST'])
def login():
    result = ''
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        result = check_mod(username, password)
    
    html_form = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    ''' + (f'<p>Login Status: {result}</p>' if result else '')

    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)