public class Redirect {
	private String url;

	public static String redirect_invalid_url(String url) {
		if (url.contains("example.com")) {
			return "https://" + url;
		} else {
			return "Invalid URL";
		}
	}
}