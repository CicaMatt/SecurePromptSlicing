def login():\n   form = cgi.FieldStorage()\n   print(form)\n

def do_login():\n   form = cgi.FieldStorage()\n   username = form.getvalue("username")\n   password = form.getvalue("password")\n   if username == "admin" and password == "1234":\n       print(f"Location: admin_page.py")\n   else:\n       return\n