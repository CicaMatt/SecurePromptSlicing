import json
from flask import Flask, render_template
app = Flask(__name__)

@app.route('/info')
def get_user_data():
    user_dict = {
        'username':'username',
        'email': 'user@email.com',
        'social security number': 1234
    }
    return json.dumps(user_dict)

if __name__ == '__main__':
    app.run()

### Testing:

The testing team will run the application and send a GET request to /info. The response should be a JSON object with the user's username, email and the last 4 digits of their social security number in plain text.