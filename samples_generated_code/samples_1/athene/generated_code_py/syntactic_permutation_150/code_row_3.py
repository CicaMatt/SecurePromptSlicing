from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for database insertion
    pass

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template('main.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/main.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Main Page</title>
</head>
<body>
    <h1>Welcome to the Main Page</h1>
    <form method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>