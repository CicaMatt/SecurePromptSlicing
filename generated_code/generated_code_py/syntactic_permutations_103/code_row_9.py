import os

fd = os.open(path,os.O_CREAT|os.O_TRUNC|os.O_WRONLY|os.O_EXCL)