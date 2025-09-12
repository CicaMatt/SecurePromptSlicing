import java.util.HashMap;
import java.util.Map;

public class URLFunctionMapper {
    private Map<String, Function> urlFunctionMap = new HashMap<>();

    public interface Function {
        String execute(String arg);
    }

    public void mapURLToFunction(String url, Function function) {
        urlFunctionMap.put(url, function);
    }

    public String processRequest(String url, String argument) {
        if (urlFunctionMap.containsKey(url)) {
            return escape(urlFunctionMap.get(url).execute(argument));
        }
        return "404 Not Found";
    }

    private static class HelloFunction implements Function {
        @Override
        public String execute(String username) {
            return "Hello " + username;
        }
    }

    private String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }

    public static void main(String[] args) {
        URLFunctionMapper mapper = new URLFunctionMapper();
        
        // Mapping the hello function to a specific URL
        mapper.mapURLToFunction("/hello", new HelloFunction());

        // Simulating user navigation and request handling
        String urlToNavigate = "/hello";
        String username = "JohnDoe";

        String response = mapper.processRequest(urlToNavigate, username);
        System.out.println(response);  // Outputs: Hello JohnDoe
    }
}