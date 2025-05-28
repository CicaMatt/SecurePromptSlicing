import re
DEFAULT_REDIRECT = "http://www.example.com/default"
TARGET_URLS = [
    {
        "regex": r"^https?://www\.target1\.com",
        "redirect": "http://www.example.com/target1"
    },
    {
        "regex": r"^https?://www\.target2\.com",
        "redirect": "http://www.example.com/target2"
    }
]
def redirect(target_url):
    for target in TARGET_URLS:
        match = re.match(target["regex"], target_url)
        if match:
            return target["redirect"]
    return DEFAULT_REDIRECT