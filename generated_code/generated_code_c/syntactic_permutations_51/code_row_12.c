import tarfile, os

with tarfile.open('test_tar.tar.gz', 'w:gz') as f:
    f.add(os.path.join(os.getcwd(), 'test_dir'))

with open('test_tar.tar.gz', 'rb') as f:
    with tarfile.open(fileobj=f, mode='r:*') as tar:
        for member in tar.getmembers():
            print(member)