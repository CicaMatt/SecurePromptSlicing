from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation of database insertion
    print(f"Inserting into DB: User={username}, Message={message}")

@app.route('/', methods=['GET', 'POST'])
def submit_message():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template('main_page.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- main_page.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Submit Message</title>
</head>
<body>
    <h1>Submit Your Message</h1>
    <form method="post" action="/">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>