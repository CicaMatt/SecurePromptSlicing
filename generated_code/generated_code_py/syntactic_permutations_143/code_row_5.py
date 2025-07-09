import requests

def unsubscribe(email):
    url = "http://localhost:8000/unsubscribe?email="+email
    r = requests.get(url)
    
    if email in db:
        delete_user(email)
        mailing_list_unsubscribe(email)
        return "User has been unsubscribed"
    else:
        return "User is not subscribed"