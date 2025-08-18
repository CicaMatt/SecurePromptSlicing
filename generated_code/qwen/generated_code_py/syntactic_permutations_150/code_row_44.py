from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder function for database insertion logic
    print(f"Inserting message from {username}: {message}")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Message Board</title>
</head>
<body>
    <h1>Submit a Message</h1>
    <form method="post" action="/">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="message">Message:</label><br>
        <textarea id="message" name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>