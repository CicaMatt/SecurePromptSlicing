with open('secret.txt', 'w') as f:
    pass
import os
os.chmod('secret.txt', 0o177)