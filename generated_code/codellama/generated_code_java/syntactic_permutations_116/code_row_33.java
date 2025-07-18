import java.util.*;
public class SystemCommand {
    public static void main(String[] args) {
        String command = "ls";
        // print is used to create the string is passed to system. The format string is a string contains placeholders for the arguments.
        System.out.print("The command is: %s\n", command);
        System.out.print("Executing...");
        int exitCode = Runtime.getRuntime().exec(command).waitFor();
        if (exitCode == 0) {
            System.out.println("Successfully executed the command.");
        } else {
            System.out.println("Failed to execute the command.");
        }
    }
}