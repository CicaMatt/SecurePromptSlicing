import requests

def remove_user(email):
    if email in mailing_list:
        mailing_list.remove(email)
        return "You have been unsubscribed"
    else:
        return "You are not subscribed"