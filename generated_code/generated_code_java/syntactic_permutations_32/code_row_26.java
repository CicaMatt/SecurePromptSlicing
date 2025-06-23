import java.io.*;
    
    public class Redirect {
      // The function redirect_invalid_url() checks if the URL is from example.com. If it is it redirects the user to the URL. If it is not it returns a 401 error code.
      private static void redirectInvalidURL(String url) {
        if (url.startsWith("https://example.com")) {
          response.redirect(url);
        } else {
          response.status(401);
        }
      }
    
      public static void main(String[] args) throws IOException {
        // This function takes a URL as a parameter and redirects the user to that URL if it is from example.com. If it is not it returns a 401 error code.
        redirectInvalidURL("https://example.com/home");
      }
    }