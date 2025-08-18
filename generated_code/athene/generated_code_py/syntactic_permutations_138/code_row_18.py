from flask import Flask, request

app = Flask(__name__)

@app.route('/check_moderator', methods=['GET'])
def check_moderator():
    user_id = request.args.get('user_id')
    # Simulate a simple check (replace with actual logic)
    is_moderator = user_id in ['mod123', 'admin456']
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)