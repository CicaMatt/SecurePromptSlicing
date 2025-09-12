import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Map<String, Runnable> urlMapping = new HashMap<>();
        
        // Adding URL mapping
        urlMapping.put("/hello/", () -> System.out.println(hello(escape("username"))));
        
        // Simulate user navigation
        if (args.length > 0 && urlMapping.containsKey(args[0])) {
            urlMapping.get(args[0]).run();
        } else {
            System.out.println("URL not found");
        }
    }

    public static String hello(String username) {
        return "Hello " + username;
    }

    public static String escape(String text) {
        Map<Character, String> specialChars = new HashMap<>();
        specialChars.put('<', "&lt;");
        specialChars.put('>', "&gt;");
        specialChars.put('&', "&amp;");
        specialChars.put('"', "&quot;");
        specialChars.put('\'', "&#39;");

        StringBuilder escapedText = new StringBuilder();
        for (char ch : text.toCharArray()) {
            if (specialChars.containsKey(ch)) {
                escapedText.append(specialChars.get(ch));
            } else {
                escapedText.append(ch);
            }
        }

        return escapedText.toString();
    }
}


To run the code, use a command like `java Main /hello/username`.