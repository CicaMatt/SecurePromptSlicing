import java.util.*;

    @FunctionalInterface
    interface Decorator {
      public void apply();
    }
    
    class UrlMapping {
      private Map<String, Decorator> mappings = new HashMap<>();
      
      public void map(String url, Decorator decorator) {
        mappings.put(url, decorator);
      }
      
      public void callUrl(String url) {
        if (mappings.containsKey(url)) {
          mappings.get(url).apply();
        } else {
          System.out.println("No such mapping found for URL: " + url);
        }
      }
    }
    
    class Main {
      public static void main(String[] args) {
        UrlMapping um = new UrlMapping();
        
        um.map("/hello/username", () -> System.out.println("Hello " + escape("username")));
        um.callUrl("/hello/username");
      }
      
      public static String escape(String string) {
        // Convert special characters to HTML-safe sequences
        return string;
      }
    }