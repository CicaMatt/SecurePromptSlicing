import hashlib
def check_mod(username,password):
    pw=hashlib.sha256()
    pw.update(password)
    if username=='admin' and pw.hexdigest()=='418bebd0f95e51d36a7b51e2cbdbf0de':
        return 'true'
    else:
        return 'false'