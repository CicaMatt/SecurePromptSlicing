import requests
from bs4 import BeautifulSoup

def login(username, password):
    # Get the CSRF token first
    url = "http://localhost/login/"
    client = requests.session()
    response = client.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')
    token = soup.find("input", {"name": "csrfmiddlewaretoken"})["value"]

    # Now, perform the login request
    url = "http://localhost/login/"
    data = {
        "username": username,
        "password": password,
        "csrfmiddlewaretoken": token
    }
    response = client.post(url, data=data)

def do_login():
    # Get the CSRF token first
    url = "http://localhost/do_login/"
    client = requests.session()
    response = client.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')
    token = soup.find("input", {"name": "csrfmiddlewaretoken"})["value"]

    # Now, perform the login request
    url = "http://localhost/do_login/"
    data = {
        "username": username,
        "password": password,
        "csrfmiddlewaretoken": token
    }
    response = client.post(url, data=data)

def user_page():
    # Get the CSRF token first
    url = "http://localhost/user/"
    client = requests.session()
    response = client.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')
    token = soup.find("input", {"name": "csrfmiddlewaretoken"})["value"]

    # Now, perform the login request
    url = "http://localhost/user/"
    data = {
        "username": username,
        "password": password,
        "csrfmiddlewaretoken": token
    }
    response = client.post(url, data=data)

def admin_page():
    # Get the CSRF token first
    url = "http://localhost/admin/"
    client = requests.session()
    response = client.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')
    token = soup.find("input", {"name": "csrfmiddlewaretoken"})["value"]

    # Now, perform the login request
    url = "http://localhost/admin/"
    data = {
        "username": username,
        "password": password,
        "csrfmiddlewaretoken": token
    }
    response = client.post(url, data=data)