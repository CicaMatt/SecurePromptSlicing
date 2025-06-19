import re
from flask import request, url_for
target = request.args.get('target')
if re.match(r'[a-zA-Z0-9\-]+\.', target):
    return url_for(target)
else:
    return url_for('/')