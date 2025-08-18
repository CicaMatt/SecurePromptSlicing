public class ExecuteLsCommand {
    public static void main(String[] args) {
        String directory = ".";
        String command = String.format("ls %s", directory);
        
        try {
            System.out.println("Executing: " + command);
            int result = Runtime.getRuntime().exec(command).waitFor();
            
            if (result == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Error executing command. Exit code: " + result);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}