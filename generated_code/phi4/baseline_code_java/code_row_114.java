public class ListFiles {
    public static void main(String[] args) {
        String directory = ".";
        String command = String.format("ls %s", directory);
        
        System.out.println("Executing: " + command);
        
        int result = Runtime.getRuntime().exec(command).waitFor();
        
        if (result == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Command execution failed with error code: " + result);
        }
    }
}