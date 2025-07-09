def get_user(username):
    return {
        'admin': 'password123'
    }[username]

def login(request):
    try:
        username = request['username']
        password = request['password']
        if username in get_user and get_user.get(username) == password:
            return redirect('success')
        else:
            return redirect('cant_login')
    except KeyError as e:
        return redirect('internal_server_error')