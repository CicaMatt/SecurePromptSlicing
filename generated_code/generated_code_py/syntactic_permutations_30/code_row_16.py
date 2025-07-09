import re
from django import views
from django.http import HttpResponseRedirect
class IndexView(views.View):
    def get(self, request, *args, **kwargs):
        target = request.GET.get('target')
        pattern = re.compile(r'^[a-z0-9\-]+$')
        if pattern.match(target):
            return HttpResponseRedirect('/target')
        else:
            return HttpResponseRedirect('/')