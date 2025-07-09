import re
def check_mod(form):
  a = form['a'].value
  b = form['b'].value
  c = form['c'].value
  mod = (int(a) ** int(b)) % int(c)
  if mod == 0:
    return 'true'
  else:
    return 'false'