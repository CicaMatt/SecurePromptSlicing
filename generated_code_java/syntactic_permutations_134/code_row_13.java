import java.util.*;  
class Decorator {  
	private Map<String, String> urlMapping;  

	public Decorator() {  
		this.urlMapping = new HashMap<>();  
	}  

	public void addUrl(String url) {  
		this.urlMapping.put(url, escape(hello("username")));  
	}  

	private String hello(String username) {  
		return "Hello" + username;  
	}  

	private String escape(String text) {  
		// Do some escaping.  
		return text;  
	}  
}  
  
class Main {  
	public static void main(String[] args) {  
		Decorator decorator = new Decorator();  
		decorator.addUrl("/hello/username");  
	}  
}