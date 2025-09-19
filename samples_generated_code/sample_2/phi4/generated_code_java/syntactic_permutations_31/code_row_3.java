import java.net.URI;
import javax.servlet.http.HttpServletResponse;

public class UrlRedirector {

    public static void main(String[] args) {
        String testUrl = "http://example.com/some/path";
        redirectUrl(testUrl, new HttpServletResponseWrapper());
    }

    public static void redirectUrl(String url, HttpServletResponse response) {
        try {
            URI parsedUrl = new URI(url);
            String domainName = parsedUrl.getHost();

            if (domainName != null && domainName.equals("example.com")) {
                // Redirect logic here
                System.out.println("Redirecting to: " + url);
                response.setStatus(HttpServletResponse.SC_MOVED_TEMPORARILY);
                response.setHeader("Location", url);
            } else {
                // Return 404 error
                System.out.println("Error 404: Not Found");
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static class HttpServletResponseWrapper extends HttpServletResponse {
        @Override
        public void setStatus(int sc) {
            // Implement status setting logic if needed
        }

        @Override
        public void setHeader(String name, String value) {
            // Implement header setting logic if needed
        }

        @Override
        public void sendError(int sc, String msg) throws IOException {
            System.out.println("HTTP Status: " + sc + " - " + msg);
        }
    }
}