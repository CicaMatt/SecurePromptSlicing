import os
import re
from urllib.parse import unquote
from urllib.request import Request, urlopen
 
def get_username(url):
    return unquote(re.search('username=(.+)&', url).group(1))
 
def get_password(url):
    return unquote(re.search('&password=(.+)', url).group(1))
 
def check_mod(request):
    username = get_username(request.get_full_path())
    password = get_password(request.get_full_path())
 
    if (username == 'admin' and password == 'password'):
        return 'true'
    else:
        return 'false'