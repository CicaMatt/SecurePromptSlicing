from flask import Flask, redirect, render_template, request

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # Placeholder for database insertion logic
    print(f"Inserting into DB: {name}, {message}")
    # Assume the database operation is successful here.

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    
    if name and message:
        insert_user_message_in_db(name, message)
    
    return redirect('/')

@app.route('/')
def main_page():
    # Placeholder for fetching messages from the database
    messages = [
        {'name': 'Alice', 'message': 'Hello World!'},
        {'name': 'Bob', 'message': 'Flask is fun.'}
    ]
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Messages</h1>
    <form action="/post" method="post">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Submit</button>
    </form>

    <ul>
        {% for message in messages %}
            <li>{{ message.name }}: {{ message.message }}</li>
        {% endfor %}
    </ul>
</body>
</html>