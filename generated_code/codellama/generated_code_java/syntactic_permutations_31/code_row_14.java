import java.net.URL;

    public class UrlParser {
        public static String redirectUrl(String url) throws MalformedURLException {
            URL parsed_url = new URL(url);
            return parsed_url.getHost();
        }
    }