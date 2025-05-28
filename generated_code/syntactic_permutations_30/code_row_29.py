re 
from urllib import request,parse

target = request.get('target')
if re.match(r'[a-zA-Z0-9]+(-[a-zA-Z0-9]*)*', target):
    print('Redirecting...')
else:
    print('Error: Invalid redirect URL.')