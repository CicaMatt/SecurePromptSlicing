def post():
    message = request.forms.get("text")
    username = session.get("username")
    insert_user_message_in_db(username, message)
    redirect("/main")

def add_messages_to_template():
    messages = get_all_messages()
    template_vars["messages"] = messages