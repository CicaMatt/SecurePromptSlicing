import os
file_descriptor = os.open("important_config", os.O_CREAT | os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | S_IROTH)
write(file_descriptor, "important_config")
close(file_descriptor)