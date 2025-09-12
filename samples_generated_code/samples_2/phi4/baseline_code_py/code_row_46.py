from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simple user data for demonstration purposes
USER_DATA = {
    "admin": "password123",
    "user": "mypassword"
}

@app.route('/')
def index():
    return render_template_string('''
        <form action="/check_mod" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username in USER_DATA and USER_DATA[username] == password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)