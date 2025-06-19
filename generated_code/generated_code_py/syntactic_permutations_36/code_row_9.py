def login(username, password):
  query = f"SELECT * FROM users WHERE username='{username}' AND password='{password}'"
  
  if not check_user_exists(query):
    return redirect('/login')
  
  user = get_user(query)
  
  if not verify_password(password, user['password']):
    return redirect('/login')
  
  redirect('/home')