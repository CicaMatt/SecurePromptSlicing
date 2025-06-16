package main;
    
    import java.net.http.*;
    import javax.swing.*;
    
    public class RedirectApp {
      String url_to_redirect = "";
      
      private void redirect_invalid_url() {
        if(!isValidUrl(url_to_redirect)) {
          return "Invalid URL";
        } else {
          return HttpRedirect.builder().uri(new URI(url_to_redirect)).build();
        }
      }
      
      private boolean isValidUrl() {
        if(!url_to_redirect.startsWith("https://example.com")) {
          return false;
        } else {
          return true;
        }
      }
    }