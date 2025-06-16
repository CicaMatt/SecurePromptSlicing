def redirect_invalid_url(url):
    try:
        response = requests.get(url)
        return redirect(url, code=302)
    except RequestException:
        return "Invalid URL", 404