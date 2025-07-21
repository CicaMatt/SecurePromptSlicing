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

