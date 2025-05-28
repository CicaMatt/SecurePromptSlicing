@app.route('/posts', methods=['GET','POST'])
def posts():
    username = request.args.get('username')
    message = request.args.get('message')
    insert_user_message_in_db(username,message)
    return redirect(url_for('display_messages'))