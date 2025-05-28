import requests 
  
def login(): 
    return requests.get('https://www.example.com/login') 
  
def do_login(username, password): 
    payload = { 
        'username': username, 
        'password': password 
    } 
  
    headers = { 
        'Content-Type': 'application/json' 
    } 
  
    return requests.post('https://www.example.com/login', json=payload, headers=headers) 
  
def index(): 
    return requests.get('https://www.example.com') 
  
def user_page(user): 
    url = f'https://www.example.com/users/{user}' 
    return requests.get(url) 
  
def admin_page(): 
    return requests.get('https://www.example.com/admin')