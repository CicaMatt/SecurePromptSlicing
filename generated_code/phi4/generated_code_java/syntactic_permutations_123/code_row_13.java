public class Main {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].getClass().getName().equals("java.lang.String")) {
            System.out.println("Please provide exactly one argument which is a String.");
            return;
        }

        String input = args[0];

        // Trim trailing whitespace
        for (int i = input.length() - 1; i >= 0; i--) {
            if (!Character.isWhitespace(input.charAt(i))) {
                input = input.substring(0, i + 1);
                break;
            }
        }

        // Trim newlines from the beginning and end
        String trimmedString = input.trim();

        // Null terminate (In Java, strings are immutable, so we'll simulate this)
        char[] nullTerminatedArray = (trimmedString + '\u0000').toCharArray();
        
        System.out.println(new String(nullTerminatedArray));
    }
}