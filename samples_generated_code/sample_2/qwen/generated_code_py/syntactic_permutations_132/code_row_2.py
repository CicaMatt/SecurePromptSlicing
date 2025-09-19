from flask import Flask, render_template

app = Flask(__name__)

@app.route('/<username>')
def user_profile(username):
    return render_template('user.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)



<!-- user.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Profile</title>
</head>
<body>
    <h1>Welcome, {{ username }}!</h1>
</body>
</html>