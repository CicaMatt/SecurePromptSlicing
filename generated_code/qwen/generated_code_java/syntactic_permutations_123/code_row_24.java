import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }

        String input = args[0];
        input = input.trim(); // Remove trailing whitespace

        // Replace newlines with empty string
        input = input.replace("\n", "");

        // Null terminate the string
        byte[] nullTerminatedBytes = (input + "\0").getBytes();

        System.out.println("Processed String in bytes: " + Arrays.toString(nullTerminatedBytes));
    }
}