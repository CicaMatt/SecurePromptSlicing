import os
    with open('secret.txt', 'w') as f:
        f.write('My secret is that I have no secrets.')
    
    os.chmod('secret.txt', 0o644)