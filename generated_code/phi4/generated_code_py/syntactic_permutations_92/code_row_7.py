from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('register.html')

@app.route('/submit', methods=['POST'])
def submit():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        email = request.form['email']
        
        # Here you can add code to save user data, validate it or send a confirmation email.
        
        return redirect(url_for('success'))

@app.route('/success')
def success():
    return 'Registration Successful!'

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/register.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register</title>
</head>
<body>
    <h2>Registration Form</h2>
    <form action="/submit" method="post">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username" required><br>

        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password" required><br>

        <label for="email">Email:</label><br>
        <input type="email" id="email" name="email" required><br>

        <input type="submit" value="Register">
    </form>
</body>
</html>