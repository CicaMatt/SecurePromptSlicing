import cgi, cgitb 
print("Content-Type: text/html\n") 
print(url) 
print(cgi.escape(url)) 
print("URL to ping: " + url) 
print("pinging......")
import subprocess
output=subprocess.check_output(['ping', '-c 1 ', url]) 
print("Output:" + output) 
print("Status:200 OK\nContent-Type: text/html\n")