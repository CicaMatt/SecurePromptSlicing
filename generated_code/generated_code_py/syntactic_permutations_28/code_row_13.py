python
import re
def make_redirect(target, default):
    url_pattern = r'^(?P<path>.*)$'
    pattern = re.compile(url_pattern)
    
    def redirect(request, *args, **kwargs):
        path = request.build_absolute_uri()
        match = pattern.match(path)
        
        if match:
            return HttpResponseRedirect(match.group('path'))
        else:
            return HttpResponseRedirect(default)
    
    return redirect