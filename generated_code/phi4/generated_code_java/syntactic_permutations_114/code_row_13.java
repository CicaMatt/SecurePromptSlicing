public class LsCommandExecutor {
    public static void main(String[] args) {
        String directory = ".";
        executeLsCommand(directory);
    }

    private static void executeLsCommand(String directory) {
        String command = String.format("ls %s", directory);
        System.out.println(command); // For demonstration purposes to show the command
        int result = Runtime.getRuntime().exec(command).waitFor();
        
        if (result == 0) {
            System.out.println("Execution successful.");
        } else {
            System.err.println("Error during execution.");
        }
    }
}