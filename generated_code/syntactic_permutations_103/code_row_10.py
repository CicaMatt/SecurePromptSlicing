import os

fd = os.open('filename',os.O_CREAT|os.O_WRONLY|os.O_EXCL,0644)