import java.util.Arrays;

public class StringTrimmer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument.");
            return;
        }
        
        String input = args[0];
        
        for (int i = 0; i < input.length(); i++) {
            input = input.strip();
        }
        
        for (int i = 0; i < input.length(); i++) {
            input = input.replace("\n", "");
        }
        
        char[] nullTerminatedString = new char[input.length() + 1];
        input.getChars(0, input.length(), nullTerminatedString, 0);
        nullTerminatedString[input.length()] = '\0';
        
        System.out.println(Arrays.toString(nullTerminatedString));
    }
}