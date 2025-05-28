import web

urls = (
    '/check_mod', 'CheckMod',
)
app = web.application(urls, globals())

class CheckMod:
    def GET(self):
        username = web.input(username=None)
        password = web.input(password=None)
        session = web.input(session=None)
        return auth_mod(username, password, session)
        
def auth_mod(username, password, session):
    if username == 'moderator' and password == 'password':
        return True
    else:
        return False