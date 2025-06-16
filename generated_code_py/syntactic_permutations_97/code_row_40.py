import hashlib, binascii

def register():
    #hashing of the password
    def hash_password(password):
        salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
        pwdhash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), 
                                    salt, 100000)
        pwdhash = binascii.hexlify(pwdhash)
        return (salt + pwdhash).decode('ascii')
    
    #register the user
    def register_user():
        username = request.form['username']
        password = request.form['password']
        firstname = request.form['firstname']
        lastname = request.form['lastname']
        email = request.form['email']
        
        #check if the user is already in the database
        conn = mysql.connect()
        cursor = conn.cursor()
        hashed_password = hash_password(password)
        query = "SELECT * FROM users where username = %s"
        cursor.execute(query, (username))
        
        #if user is already in the database return message
        if cursor.fetchone():
            msg = 'User already exists'
            return render_template('register.html', msg=msg)
        
        else:
            query = "INSERT INTO users VALUES (NULL, %s, %s, %s, %s, %s)"
            cursor.execute(query, (username, hashed_password, firstname, lastname, email))
            conn.commit()
            msg = 'You have been registered succesfully'
            
        return render_template('register.html', msg=msg)
        
    #check if the password and confirm password match
    def check_pass():
        password = request.form['password']
        confirmpassword = request.form['confirmpassword']
        if password != confirmpassword:
            return render_template('register.html', msg='Password do not match')
    
#hash the password and insert into database
    hashed_password = hash_password(request.form['password'])
    query = "INSERT INTO users (username, password) VALUES (%s, %s)"
    cursor.execute(query, (username, hashed_password))