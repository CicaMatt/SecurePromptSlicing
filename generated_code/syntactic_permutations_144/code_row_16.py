import subprocess

def check_email(email, db):
    if not db.contains(email):
        return 0
    else:
        process = subprocess.Popen(['./unsubscribe', email], stdout=subprocess.PIPE)
        output = process.communicate()[0]
        if output == b'0':
            return 1
        else:
            return 0