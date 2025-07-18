import re
from django.http import HttpResponseRedirect

def my_view(request):
    regex = '^[a-zA-Z0-9\-]+\.[a-zA-Z]+'
    target = request.GET['target']
    if re.match(regex, target):
        return HttpResponseRedirect('http://www.google.com')
    else:
        return HttpResponseRedirect('/')