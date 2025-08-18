from flask import request, redirect, url_for

def handle_message_submission():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

# Assuming the main page route is defined as follows:
def main_page():
    # Your existing code for rendering the main page
    return '''
        <form method="post" action="/submit_message">
            <input type="text" name="username" placeholder="Username" required>
            <textarea name="message" placeholder="Message" required></textarea>
            <button type="submit">Submit</button>
        </form>
    '''

# Dummy function for database insertion
def insert_user_message_in_db(username, message):
    # Your code to insert the message into the database
    pass

# Example Flask app setup
from flask import Flask
app = Flask(__name__)

@app.route('/')
def index():
    return main_page()

@app.route('/submit_message', methods=['POST'])
def submit_message():
    return handle_message_submission()

if __name__ == '__main__':
    app.run(debug=True)