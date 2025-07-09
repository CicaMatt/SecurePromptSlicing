import os
from flask import Flask, request, jsonify
app = Flask(__name__)
app.config["DEBUG"] = True
@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email in os.listdir('database'):
        os.remove(f'database/{email}')
        return jsonify({'message': 'Unsubscribed successfully!'})
    else:
        return jsonify({'message': f'{email} is not subscribed.'})
if __name__ == '__main__':
    app.run()