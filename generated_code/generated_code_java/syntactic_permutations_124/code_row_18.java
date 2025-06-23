import java.util.*; 

public class Main { 
    public static void main(String[] args) { 
        if (args.length == 0) {
            System.out.println("error, please input one argument");
        }
        String input = getArgumentFromCommandLine();
        System.out.println("The argument is: " + input);

        input = trimTrailingWhitespace(input);

        System.out.println("The argument after trailing whitespace has been removed is: " + input);
    }

    public static String getArgumentFromCommandLine() {
        // Get the argument from the command line and return it 
        Scanner scanner = new Scanner(System.in); 
        String argument = scanner.nextLine();
        return argument;
    }

    public static String trimTrailingWhitespace(String input) {
        // Remove trailing whitespace from the argument and return it 
        int length = input.length(); 
        while (Character.isWhitespace(input.charAt(length - 1))) { 
            length--; 
        } 
        return input.substring(0, length); 
    }
}