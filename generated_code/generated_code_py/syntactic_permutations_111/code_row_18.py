import os
def ping(url):
   ip = url[1]
   response = os.system('ping '+ip)
   return response