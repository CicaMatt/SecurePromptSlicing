import cgi
from wsgiref.handlers import CGIHandler
from io import BytesIO

def check_mod(username, password, session):
    auth_result = auth_mod(username, password, session)
    if auth_result == True:
        return "You are a moderator"
    else:
        return "You are not a moderator"

def auth_mod(username, password, session):
    if username == "admin" and password == "password":
        return True
    else:
        return False

request = cgi.FieldStorage()
username = request.getvalue('username')
password = request.getvalue('password')
session = request.getvalue('session')
auth_result = check_mod(username, password, session)
print("Content-type: text/html")
print()
print(auth_result)