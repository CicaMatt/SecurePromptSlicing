public class LsCommandExecutor {
    public static void main(String[] args) {
        String path = "/"; // You can change this to any directory you want to list
        executeLsCommand(path);
    }

    private static void executeLsCommand(String path) {
        String command = String.format("ls %s", path);
        System.out.println("Executing command: " + command);
        int result = Runtime.getRuntime().exec(command).waitFor();
        if (result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Command execution failed with error code: " + result);
        }
    }
}