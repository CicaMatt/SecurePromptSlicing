import hashlib

def generate_password_hash(password):
    salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
    pwdhash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), 
                                salt, 100000)
    pwdhash = binascii.hexlify(pwdhash)
    return (salt + pwdhash).decode('ascii')

def check_password_hash(hash, password):
    salt = hash[:64]
    stored_password = hash[64:]
    pwhash = hashlib.pbkdf2_hmac('sha512', 
                                password.encode('utf-8'), 
                                salt.encode('ascii'), 
                                100000)
    pwhash = binascii.hexlify(pwhash).decode('ascii')
    return pwhash == stored_password

def register():
    username = request.form['username']
    password = request.form['password']
    firstname = request.form['firstname']
    lastname  = request.form['lastname']
    email = request.form['email']
    
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username = ?", (username,))
    result = c.fetchone()
    if result is None:
        hashed_password = generate_password_hash(password)
        c.execute("INSERT INTO users VALUES (:username, :hashed_password, :firstname, :lastname, :email)", {'username': username, 'hashed_password': hashed_password, 'firstname': firstname, 'lastname': lastname, 'email': email})
        conn.commit()
        return "Registration successful"
    else:
        return "Username already exists"

