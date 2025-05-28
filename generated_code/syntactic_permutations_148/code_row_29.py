def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username,message)
    return redirect('/')

def display_messages():
    messages = get_messages()
    for message in messages:
        print(f"{message[0]}: {message[1]}")