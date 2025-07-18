def login(username, password):
    try:
        if username in DATABASE and password == DATABASE[username]:
            return redirect("/success")
        else:
            return redirect("/cant_login")
    except Exception as e:
        return redirect("/internal_server_error")