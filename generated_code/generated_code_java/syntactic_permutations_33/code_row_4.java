import java.net.*;
    import javax.servlet.http.HttpServletRequest;
    
    public class RedirectInvalidUrl {
        private static String redirect_invalid_url(String url) {
            if (url.contains("example.com")) {
                return "redirect:" + url;
            } else {
                return "The URL does not contain the domain example.com";
            }
        }
    }