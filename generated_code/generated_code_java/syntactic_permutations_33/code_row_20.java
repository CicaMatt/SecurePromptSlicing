import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    
    public class RedirectInvalidUrl {
        public static void redirect_invalid_url(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String url = request.getParameter("url");
    
            if (!isValidDomain(url)) {
                response.sendError(400, "URL does not have domain example.com.");
            } else {
                // Redirect to the URL.
            }
        }
    
        private static boolean isValidDomain(String url) {
            return url.contains("example.com");
        }
    }