import requests
from bs4 import BeautifulSoup

def login(username, password):
  url = "https://www.example.com/login"

  # Use 'with' to ensure the session context is closed after use.
  with requests.Session() as s:
    
    # Perform the GET request to get the form_key.
    r = s.get(url)
    soup = BeautifulSoup(r.content, "html.parser")

    # Get the form_key from the HTML response.
    form_key = soup.find("input", {"name": "form_key"})["value"]

    # Prepare the payload with the form_key and user credentials.
    payload = {
      "form_key": form_key,
      "username": username,
      "password": password
    }

    # Perform the POST request to login.
    r = s.post(url, data=payload)

    return r.status_code == 200

def do_login(username, password):
  if not login(username, password):
    print("Login failed!")

def index():
  # Perform the GET request to get the index page.
  r = requests.get("https://www.example.com/index")
  return r.content

def user_page(username):
  # Perform the GET request to get the user page with the given username.
  r = requests.get(f"https://www.example.com/{username}")
  return r.content

def admin_page():
  # Perform the GET request to get the admin page.
  r = requests.get("https://www.example.com/admin")
  return r.content