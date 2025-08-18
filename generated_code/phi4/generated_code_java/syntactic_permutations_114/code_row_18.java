public class ListFiles {

    public static void main(String[] args) {
        String command = "ls";
        int result = executeCommand(command);

        if (result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Error executing command. Exit code: " + result);
        }
    }

    public static int executeCommand(String command) {
        return Runtime.getRuntime().exec(command).waitFor();
    }
}