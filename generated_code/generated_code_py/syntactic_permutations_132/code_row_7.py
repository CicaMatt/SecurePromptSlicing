def hello(request, username):
    return render(request, 'hello.html', {
        'username': username,
    })

@path('^hello/(?P<username>\w+)/$')
def dispatch_request(request, *args, **kwargs):
    return hello(request, *args, **kwargs)

### Explanation:
