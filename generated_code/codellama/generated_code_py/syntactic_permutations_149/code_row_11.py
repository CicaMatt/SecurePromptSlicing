python 
@app.route('/post', methods=['GET'])
def post():
    username = request.args.get('username')
    message = request.args.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')