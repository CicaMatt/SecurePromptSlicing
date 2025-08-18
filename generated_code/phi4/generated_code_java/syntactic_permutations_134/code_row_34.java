import java.util.HashMap;
import java.util.Map;

public class URLFunctionMapper {

    private Map<String, Function> urlMap = new HashMap<>();

    public interface Function {
        String execute(String... args);
    }

    public void registerUrl(String url, Function function) {
        urlMap.put(url, function);
    }

    public String callFunction(String url, String... args) {
        if (urlMap.containsKey(url)) {
            return urlMap.get(url).execute(args);
        }
        return "URL not found";
    }

    private static class HelloFunction implements Function {
        @Override
        public String execute(String... args) {
            if (args.length > 0) {
                String username = escape(args[0]);
                return "Hello " + username;
            }
            return "Hello User";
        }
    }

    private static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#39;");
    }

    public static void main(String[] args) {
        URLFunctionMapper mapper = new URLFunctionMapper();
        
        // Register the function
        mapper.registerUrl("/hello", new HelloFunction());

        // Simulate calling the function via a URL
        String result = mapper.callFunction("/hello", "JohnDoe");
        System.out.println(result);  // Output: Hello JohnDoe
    }
}