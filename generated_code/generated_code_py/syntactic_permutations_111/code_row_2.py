def ping():
    """Ping a URL"""
    url = input("Enter a URL to Ping : ") 
    return os.system('ping -c 3 ' + url)