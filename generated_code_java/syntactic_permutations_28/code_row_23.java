import java.util.regex.Pattern;

public class Redirect {
    private Pattern pattern;
    public Redirect(String regex) {
        this.pattern = Pattern.compile(regex);
    }

    public void handleRequest(String target) {
        if (this.pattern.matcher(target).matches()) {
            // redirect to target URL
        } else {
            // don't do anything
        }
    }
}