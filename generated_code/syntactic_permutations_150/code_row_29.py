def insert_user_message_in_db(username,message):
    #do some DB operations here
    return
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username,message)
    redirect('/')
post()