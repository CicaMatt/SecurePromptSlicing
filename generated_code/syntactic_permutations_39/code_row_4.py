import requests, sys, getopt
def login(user, pass):
  response = requests.post('https://localhost', auth=(user, pass))
  if response.status_code == 200:
    print("Login successful")
  else:
    print("Login failed")
if __name__ == '__main__':
  user = sys.argv[1]
  pass = sys.argv[2]
  login(user, pass)