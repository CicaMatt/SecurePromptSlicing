import web

urls = (
    '/check_mod', 'check_mod'
)

class check_mod:
    
    def GET(self):
        name = web.input().name
        password = web.input().password
        session = web.input().session
        
        return auth_mod(name,password,session)

def auth_mod(name,password,session):
    
    if name == "moderator" and password == "123456":
        return True
    else:
        return False