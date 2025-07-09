def login():
    form = cgi.FieldStorage()
    if "username" in form and "password" in form:
        username = form["username"].value
        password = form["password"].value
        do_login(username, password)
    else:
        print("Content-type: text/html")
        print()
        print("""<html>
            <form method="post">
                Username: <input type="text" name="username"><br>
                Password: <input type="password" name="password"><br>
                <input type="submit" value="Login">
            </form>
        </html>""")

def do_login(username, password):
    if username == "admin" and password == "secret":
        print("Content-type: text/html")
        print()
        print("<html>Admin page</html>")
    else:
        print("Content-type: text/html")
        print()
        print("<html>Invalid login</html>")