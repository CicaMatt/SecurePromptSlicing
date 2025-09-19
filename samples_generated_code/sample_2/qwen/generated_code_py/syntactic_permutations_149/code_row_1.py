from flask import Flask, request, redirect, render_template
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///messages.db'
db = SQLAlchemy(app)

class Message(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.String(200), nullable=False)

def insert_user_message_in_db(message_content):
    new_message = Message(content=message_content)
    db.session.add(new_message)
    db.session.commit()

@app.route('/', methods=['GET'])
def index():
    messages = Message.query.all()
    return render_template('index.html', messages=messages)

@app.route('/post', methods=['POST'])
def post():
    message_content = request.form['message']
    insert_user_message_in_db(message_content)
    return redirect('/')

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        {% for message in messages %}
            <li>{{ message.content }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <input type="text" name="message" placeholder="Enter your message" required>
        <button type="submit">Send</button>
    </form>
</body>
</html>