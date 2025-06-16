import java.util.HashMap;
    public class Decorator {
    	private HashMap<String, Function> mappings = new HashMap<>();
    	public void addMapping(String url, Function func) {
    	mappings.put(url, func);
    	}
    	public String getURLForFunc(Function func) {
    	for (String url : mappings.keySet()) {
    	if (mappings.get(url).equals(func)) {
    	return url;
    	}
    	}
    	return null;
    	}
    }
    public class HelloDecorator extends Decorator {
    	public String hello() {
    	String username = "username";
    	return "Hello, " + escape(username) + "!";
    	}
    	private String escape(String str) {
    	// Convert special characters to HTML-safe sequences.
    	return str;
    	}
    }
    public class Controller {
    	public void navigateToURL(String url) {
    	Function func = mappings.get(url);
    	if (func != null) {
    	// Call the function associated with this URL.
    	}
    	else {
    	// Handle 404 error.
    	}
    }