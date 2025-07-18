import os
    
    def create_new_file(path, contents=None):
        with open(path, "w", encoding="utf-8") as f:
            if contents is not None:
                f.write(contents)
        return True
        
        # Tests
        assert create_new_<s>    file("file.txt", "Hello World!") == True