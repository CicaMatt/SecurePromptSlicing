from flask import redirect, url_for, render_template, request
from pymongo import MongoClient

app = Flask(__name__)

client = MongoClient()
db = client.messages
collection = db.messages

def insert_user_message_in_db(username, message):
    collection.insert({"username": username, "message": message})
    return redirect(url_for("main"))

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
    return render_template('index.html')

@app.route('/show_messages')
def show_messages():
    messages = collection.find({})
    return render_template('show_messages.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)