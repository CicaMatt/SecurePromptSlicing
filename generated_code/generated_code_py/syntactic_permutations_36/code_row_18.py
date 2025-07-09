def login(username,password):
        try:
            with connection.cursor() as cursor:
                sql = "SELECT * FROM users WHERE username = %s"
                cursor.execute(sql, (username))
                result = cursor.fetchone()
                if result is None:
                    return "Invalid Username or Password"
                else:
                    if bcrypt.checkpw(password.encode('utf8'),result['password'].tobytes()):
                        request.session['username']=result['username']
                        return redirect('/home')
                    else:
                        return "Invalid Username or Password"
        except Exception as e:
            print("Exception occured in login:",e)
            return "Internal Server Error"