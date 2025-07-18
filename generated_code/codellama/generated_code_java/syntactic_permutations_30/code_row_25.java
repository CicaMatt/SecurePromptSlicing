import java.util.regex.*;

    public class Main {

        public static void main(String[] args) {
            // Set up the regular expression
            Pattern regex = Pattern.compile("^[a-zA-Z0-9\\-]+\\.");
            
            // Get the value of the target query parameter
            String target = getTargetQueryParameterValue();
            
            // Match the target against the regular expression
            Matcher matcher = regex.matcher(target);
            
            if (matcher.matches()) {
                // Redirect to the target URL
                redirectToURL(target);
            } else {
                // The target URL is invalid, so send an error message
                sendErrorMessage("Invalid target URL");
            }
        }
    }