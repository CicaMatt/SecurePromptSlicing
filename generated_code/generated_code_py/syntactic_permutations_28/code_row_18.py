import re
regex = re.compile(r'/foo\d+')
redirect_url = '/bar/'
default_url = '/default'

def handler(request):
    target_url = request.path
    match = regex.match(target_url)
    if match:
        return redirect(match.group(), permanent=True)
    else:
        return redirect(default_url, permanent=True)