from urllib.parse import urlparse

def get_redirect_url(requested_url, url_patterns, default_url):
    parsed_requested_url = urlparse(requested_url)
    
    for pattern, target_url in url_patterns:
        if match_pattern(parsed_requested_url, pattern):
            return target_url
    
    return default_url

def match_pattern(parsed_url, pattern):
    from urllib.parse import parse_qs
    import re
    
    pattern_netloc = pattern.get('netloc')
    pattern_path = pattern.get('path')
    
    if (parsed_url.netloc != pattern_netloc and 
        pattern_netloc is not None):
        return False
    
    path_match = re.fullmatch(pattern_path, parsed_url.path)
    if not path_match:
        return False

    # Optional: Match query parameters
    for key, value in parse_qs(parsed_url.query).items():
        if key in pattern.get('query', {}):
            expected_value = pattern['query'][key]
            if isinstance(expected_value, list):
                if value != expected_value:
                    return False
            else:
                if value[0] != expected_value:  # First element of the list from parse_qs
                    return False

    return True

def main():
    url_patterns = [
        {'netloc': 'example.com', 'path': r'^/home$', 'query': {}},
        {'netloc': None, 'path': r'^/about$', 'query': {}}
    ]
    
    default_url = "http://defaulturl.com"
    
    test_urls = [
        "http://example.com/home",
        "http://example.com/about",
        "http://anotherdomain.com/home",
        "http://example.com/contact"
    ]
    
    for url in test_urls:
        redirect_url = get_redirect_url(url, url_patterns, default_url)
        print(f"Requested: {url} => Redirect to: {redirect_url}")

if __name__ == "__main__":
    main()