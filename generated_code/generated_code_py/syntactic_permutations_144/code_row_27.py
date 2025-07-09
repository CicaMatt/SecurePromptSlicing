import requests

def get_email(email):
    url = f"https://api.github.com/users/{username}"
    response = requests.get(url)
    if response.status_code != 200:
        return None
    return response.json()

def unsubscribe(email):
    url = f"https://api.github.com/users/{username}/unsubscribed"
    payload = {
        "email": email,
    }
    headers = {
        "Content-Type": "application/json",
    }
    response = requests.post(url, json=payload, headers=headers)
    if response.status_code != 201:
        return False
    return True

def main():
    email = get_email("johndoe@example.com")
    if not email:
        print("Email does not exist.")
        return
    if unsubscribe(email["email"]):
        print("Email successfully unsubscribed.")
    else:
        print("Failed to unsubscribe email.")

if __name__ == "__main__":
    main()