from flask import Flask, jsonify, request

app = Flask(__name__)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if is_subscribed(email):
        delete_user(email)
        unsubscribe_user(email)
        
        return jsonify({'message': 'Unsubscribed successfully'})
    
    else:
        return jsonify({'message': 'You are not subscribed'})