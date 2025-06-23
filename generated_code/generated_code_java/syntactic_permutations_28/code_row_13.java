package myapp;

import java.util.regex.Pattern;

public class Redirect {
	private Pattern pattern;
	private String target;
	private String defaultTarget;
	
	public Redirect(String pattern, String target, String defaultTarget) {
		this.pattern = Pattern.compile(pattern);
		this.target = target;
		this.defaultTarget = defaultTarget;
	}
	
	public boolean matches(String url) {
		return pattern.matcher(url).matches();
	}
	
	public String getTarget(String url) {
		if (matches(url)) {
			return target;
		} else {
			return defaultTarget;
		}
	}
}