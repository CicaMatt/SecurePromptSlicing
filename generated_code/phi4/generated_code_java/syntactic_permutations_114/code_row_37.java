public class ListFiles {
    public static void main(String[] args) {
        String command = String.format("ls %s", "your_directory_here");
        System.out.println(command);
        System.out.println("Executing command: " + command);
        int result = Runtime.getRuntime().exec(command).waitFor();
        if (result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Command execution failed with error code: " + result);
        }
    }
}