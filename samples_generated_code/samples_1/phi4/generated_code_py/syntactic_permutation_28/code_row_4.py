from typing import Optional

class RedirectManager:
    def __init__(self, default_url: str):
        self.default_url = default_url

    def get_redirect_url(self, url: str) -> str:
        if self.is_target_url(url):
            return url
        else:
            return self.default_url

    @staticmethod
    def is_target_url(target_url: str) -> bool:
        # Replace this with actual URL matching logic as required.
        target_urls = {
            "https://example.com/page1",
            "https://example.com/page2"
        }
        return target_url in target_urls


# Example usage
redirect_manager = RedirectManager(default_url="https://default.com")

requested_url = "https://example.com/page1"
redirect_url = redirect_manager.get_redirect_url(requested_url)
print(redirect_url)  # Outputs: https://example.com/page1

requested_url = "https://randomsite.com"
redirect_url = redirect_manager.get_redirect_url(requested_url)
print(redirect_url)  # Outputs: https://default.com