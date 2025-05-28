import cgi
from db import connect
from db import create_order

form = cgi.FieldStorage()
username = form["username"].value
quantity = form["quantity"].value

create_order(username, quantity)

print("Content-type: text/html")
print("Location: /profile")
print()