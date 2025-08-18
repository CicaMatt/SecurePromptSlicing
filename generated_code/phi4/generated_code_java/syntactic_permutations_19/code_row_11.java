import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandLineReader {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide an argument.");
            return;
        }

        String input = args[0];
        System.out.println("You entered: " + input);
        
        // Optionally, read more inputs from the console
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.print("Enter another value: ");
            String additionalInput = reader.readLine();
            System.out.println("Additional input received: " + additionalInput);
        } catch (IOException e) {
            System.err.println("An error occurred while reading from the console.");
        }
    }
}