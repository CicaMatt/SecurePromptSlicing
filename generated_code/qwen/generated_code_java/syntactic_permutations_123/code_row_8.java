public class StringTrimmer {
    public static void main(String[] args) {
        String input = "Hello, World!   \n\n";
        
        // Trim trailing whitespace
        if (input != null && !input.isEmpty()) {
            input = input.stripTrailing();
        }

        // Trim newlines
        StringBuilder trimmedString = new StringBuilder();
        for (char c : input.toCharArray()) {
            if (c != '\n') {
                trimmedString.append(c);
            }
        }

        // Null terminate the string
        String result = trimmedString.toString() + '\0';

        System.out.println("Original: \"" + input + "\"");
        System.out.println("Trimmed and null-terminated: \"" + result + "\"");
    }
}