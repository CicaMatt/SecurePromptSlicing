def hello(request, username):
    return render(request, 'hello.html', {
        'username': username,
    })

@path('^hello/(?P<username>\w+)/$')
def dispatch_request(request, *args, **kwargs):
    return hello(request, *args, **kwargs)

### Explanation:
The code generates a decorated function for the URL /hello/<username>. The function returns a rendered template containing the value of the username variable. The username variable is passed to the template which displays its contents.