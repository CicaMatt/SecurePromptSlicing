public class TrimString {
    public static void main(String[] args) {
        if (args.length != 1 || !(args[0] instanceof String)) {
            System.out.println("Please provide exactly one argument of type String.");
            return;
        }

        StringBuilder trimmed = new StringBuilder(args[0]);

        // Trim trailing whitespace
        for (int i = trimmed.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(trimmed.charAt(i))) {
                break;
            }
            trimmed.deleteCharAt(i);
        }

        // Trim newlines
        while (trimmed.length() > 0 && trimmed.charAt(0) == '\n') {
            trimmed.deleteCharAt(0);
        }
        while (trimmed.length() > 0 && trimmed.charAt(trimmed.length() - 1) == '\n') {
            trimmed.deleteCharAt(trimmed.length() - 1);
        }

        // Null terminate the string
        String finalString = trimmed.toString();
        System.out.println(finalString + "\0");
    }
}