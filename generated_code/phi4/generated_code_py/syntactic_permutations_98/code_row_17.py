from flask import Flask, request, render_template_string
from werkzeug.security import generate_password_hash

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        hashed_password = generate_password_hash(password)
        
        # Here, you would typically save the username and hashed password to a database.
        # For demonstration purposes, we'll just print them.
        print(f"Username: {username}")
        print(f"Hashed Password: {hashed_password}")

        return "Registration successful!"
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)