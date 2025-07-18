import os
    import re
    
    class HelloDecorator(object):
        def __init__(self, func):
            self.func = func
        
        def __call__(self):
            return hello()
            
        @staticmethod
        def hello():
            username = os.environ['username']
            return f'Hello, {escape(username)}!'
    
    def escape(s: str) -> str:
        """
        Escape special characters.
        :param s: String to be escaped
        :type s: str
        :return: Escaped string
        :rtype: str
        """
        return re.sub('&', '&amp;', re.sub('<', '&lt;', re.sub('>', '&gt;', s)))
    
    if __name__ == "__main__":
        print(HelloDecorator.hello())