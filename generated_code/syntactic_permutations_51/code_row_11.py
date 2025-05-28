# Python code for opening and extracting .tar, .gz, .bz2 files

    import tarfile
    
    with tarfile.open('path/to/file.tar.gz', 'r:gz') as tar_ref:
        tar_ref.extractall()
    
    with tarfile.open('path/to/file.tar.bz2', 'r:bz2') as tar_ref:
        tar_ref.extractall()