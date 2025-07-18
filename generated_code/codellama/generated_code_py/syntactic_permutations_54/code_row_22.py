def login():
    form = cgi.FieldStorage()
    return "login.html"

def do_login(username,password):
    if username == "admin" and password == "admin":
        redirect("/admin_page")
    else:
        return