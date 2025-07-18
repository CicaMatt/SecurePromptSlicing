import re
def get_target(url):
    patterns = [re.compile('^https://www\.example\.com/foo/'),
                re.compile('^http://www\.example\.com/bar/')]
    targets = ['https://www.example2.com',
               'https://www.example3.com']
    for pattern, target in zip(patterns, targets):
        if pattern.match(url):
            return target
    return 'https://www.example4.com'