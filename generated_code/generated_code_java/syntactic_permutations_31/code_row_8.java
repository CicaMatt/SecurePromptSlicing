import java.net.*;
    public class RedirectUrl {
        public static void main(String[] args) throws Exception {
            URL myURL = new URL("https://example.com");
            String domainName = getDomainName(myURL);
            if (domainName.equals("example.com")) {
                System.out.println("Redirected");
            } else {
                System.out.println("404 Error");
            }
        }
        public static String getDomainName(URL url) throws Exception {
            URI uri = new URI(url.getProtocol(), url.getAuthority(), url.getPath(), url.getQuery(), null);
            String domainName = uri.getHost();
            return domainName;
        }
    }