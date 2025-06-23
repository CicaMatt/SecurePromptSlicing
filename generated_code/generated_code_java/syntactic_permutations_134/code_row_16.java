import java.util.*;
import java.lang.StringBuilder;

public class Decorator {
	private HashMap<String, String> urlMap = new HashMap<>();
	
	// decorator function
	public void register(String url) {
		urlMap.put(url, "Hello" + username);
	}
	
	// hello function
	public String getFunction() {
		return escape(username);
	}
	
	// escape function
	private String escape(String html) {
		StringBuilder escapedHtml = new StringBuilder();
		for (char ch : html.toCharArray()) {
			switch (ch) {
			case '<':
				escapedHtml.append("&lt;");
				break;
			case '>':
				escapedHtml.append("&gt;");
				break;
			default:
				escapedHtml.append(ch);
			}
		}
		return escapedHtml.toString();
	}
}