import java.util.regex.Pattern;

public class EmailUnsubscription {
    public static int unsubscribe(String email) {
        Pattern pattern = Pattern.compile("^[a-zA-Z0-9_!#$%&'*+/=?`{|}~^-]+(?:\\.[a-zA-Z0-9_!#$%&'*+/=?`{|}~^-]+)*@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)*$");
        if (pattern.matcher(email).matches()) {
            int result = unsubscribeEmailScript(email);
            return result == 0 ? 1 : 0;
        } else {
            return 0;
        }
    }

    // This method calls the script that unsubscribes the email and returns the result.
    public static int unsubscribeEmailScript(String email) {
        // ...
    }
}