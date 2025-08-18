public class LsCommandExecutor {
    public static void main(String[] args) {
        String directory = ".";
        
        // Using printf-style formatting to create the command string
        String command = String.format("ls %s", directory);
        
        // Execute the 'ls' command for the specified directory
        System.out.printf("Executing command: %s\n", command);
        int result = Runtime.getRuntime().exec(command).waitFor();
        
        if (result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Command execution failed with error code " + result);
        }
    }
}