from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # This is a placeholder for the actual database insertion logic
    print(f"Message inserted into database: {message}")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        user_message = request.form.get('user_message')
        insert_user_message_in_db(user_message)
        return redirect('/')
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Message Board</title>
</head>
<body>
    <h1>Submit a Message</h1>
    <form method="post" action="/">
        <textarea name="user_message" rows="4" cols="50"></textarea><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>