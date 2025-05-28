def insert_user_message_in_db(username, message):
    # code to insert into database here
    pass

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')