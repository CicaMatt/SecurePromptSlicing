import requests
import json

def check_mod(username,password,session):
    url = f"https://stackoverflow.com/users/{username}/{password}/{session}"
    response = requests.get(url)
    data = json.loads(response.text)
    auth_mod = data["items"][0]["moderator"]
    return auth_mod