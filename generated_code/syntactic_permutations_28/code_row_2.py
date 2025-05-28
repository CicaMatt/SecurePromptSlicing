import re
    regex = re.compile(r"^/(?P<name>[a-zA-Z]+)/(?P<page>[\d+])")
    def match_url(url, default):
        if regex.match(url) is not None:
            return url
        else:
            return default