import http.server
import cgi

def http_hello_page(request,response):
    form=cgi.FieldStorage(fp=request,headers=request.headers)
    username=form["username"].value
    response.write("hello {}".format(username))
    return