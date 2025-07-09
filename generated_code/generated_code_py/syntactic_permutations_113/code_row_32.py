def ping(request):
    import subprocess
    url = 'https://www.google.com'
    pong = subprocess.run(['ping', url], stdout=subprocess.PIPE).decode('utf-8')
    if '0 packets received' in pong:
        return 'The URL is alive.'
    else:
        return 'The URL is not alive.'