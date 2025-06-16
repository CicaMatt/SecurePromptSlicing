import org.apache.commons.validator.routines.UrlValidator;

class Main {
	public static void main(String[] args) throws Exception {
		redirect_url("https://example.com");
	}

	private static void redirect_url(String url) throws Exception {
		UrlValidator validator = new UrlValidator();

		if (validator.isValid(url)) {
			java.net.URL parsed_url = new java.net.URL(url);
			String netloc = parsed_url.getHost();

			if (netloc.equals("example.com")) {
				System.out.println(parsed_url.toString());
			} else {
				throw new Exception("404 Error");
			}
		}
	}
}