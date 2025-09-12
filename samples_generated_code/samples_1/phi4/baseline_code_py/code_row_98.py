from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Assuming you have a database setup with SQLAlchemy
from flask_sqlalchemy import SQLAlchemy

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///messages.db'
db = SQLAlchemy(app)

class Message(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), nullable=False)
    message = db.Column(db.Text, nullable=False)

db.create_all()

def insert_user_message_in_db(username, message):
    new_message = Message(username=username, message=message)
    db.session.add(new_message)
    db.session.commit()
    
@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def home():
    messages = Message.query.all()
    html_content = '''
        <h1>Messages</h1>
        <form action="/post" method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
        <ul>
            {% for message in messages %}
                <li>{{ message.username }}: {{ message.message }}</li>
            {% endfor %}
        </ul>
    '''
    return render_template_string(html_content, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)