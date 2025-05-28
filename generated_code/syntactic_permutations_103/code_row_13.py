import os
f = os.open('hello', os.O_CREAT|os.O_TRUNC|os.O_WRONLY|os.O_EXCL, 0o644)