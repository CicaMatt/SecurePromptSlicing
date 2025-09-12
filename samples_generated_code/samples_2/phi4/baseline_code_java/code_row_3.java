public class LsCommandExecutor {
    public static void main(String[] args) {
        String directoryPath = "."; // Default to current directory if no argument provided
        if (args.length > 0) {
            directoryPath = args[0];
        }

        executeLsCommand(directoryPath);
    }
    
    private static void executeLsCommand(String path) {
        String command = createLsCommand(path);
        System.out.println("Executing: " + command);
        int result = Runtime.getRuntime().exec(command).waitFor();
        
        if (result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Error executing command. Exit code: " + result);
        }
    }
    
    private static String createLsCommand(String path) {
        return String.format("ls %s", path);
    }
}