import java.util.HashMap;
import java.util.Map;
import java.io.IOException;

public class UrlDecorator {
    private Map<String, Function> urlFunctionMap = new HashMap<>();

    public void register(String url, Function function) {
        urlFunctionMap.put(url, function);
    }

    public String navigateToUrl(String url) throws IOException {
        if (urlFunctionMap.containsKey(url)) {
            return urlFunctionMap.get(url).execute();
        } else {
            throw new IOException("URL not found");
        }
    }

    @FunctionalInterface
    interface Function {
        String execute() throws IOException;
    }

    public static void main(String[] args) {
        UrlDecorator decorator = new UrlDecorator();

        // Register the URL and its corresponding function
        decorator.register("/username", username -> "Hello, " + escape(username));

        try {
            System.out.println(decorator.navigateToUrl("/username")); // Replace with actual username for real use
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String escape(String input) {
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }
}