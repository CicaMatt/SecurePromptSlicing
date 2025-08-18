public class StringManipulation {
    public static void main(String[] args) {
        String input = "   Hello World!  \n\n";
        
        // Trim trailing whitespaces
        StringBuilder trimmedString = new StringBuilder(input.trimEnd());
        
        // Remove newlines
        for (int i = 0; i < trimmedString.length(); ) {
            if (trimmedString.charAt(i) == '\n') {
                trimmedString.deleteCharAt(i);
            } else {
                i++;
            }
        }

        // Null-terminate the string
        StringBuilder nullTerminatedString = new StringBuilder(trimmedString.toString());
        nullTerminatedString.append('\u0000');
        
        System.out.println("Final string: \"" + nullTerminatedString.toString() + "\"");
    }
}