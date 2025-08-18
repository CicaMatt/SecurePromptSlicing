from flask import Flask, request, redirect, render_template
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///messages.db'
db = SQLAlchemy(app)

class Message(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), nullable=False)
    message = db.Column(db.String(200), nullable=False)

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    new_message = Message(username=username, message=message)
    db.session.add(new_message)
    db.session.commit()
    return redirect('/')

@app.route('/')
def index():
    messages = Message.query.all()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Messages</title>
</head>
<body>
    <form action="/post" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <input type="text" name="message" placeholder="Message" required>
        <button type="submit">Post Message</button>
    </form>
    <ul>
        {% for message in messages %}
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
        {% endfor %}
    </ul>
</body>
</html>