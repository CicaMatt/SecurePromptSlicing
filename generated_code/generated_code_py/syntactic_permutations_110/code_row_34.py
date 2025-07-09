import sys
import subprocess
def getUserInfo(user):
    result = subprocess.run(["id",user],capture_output=True,text=True)
    return result.returncode
username = sys.argv[1]
result = getUserInfo(username)
print(result)