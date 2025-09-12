public class ListDirectory {
    public static void main(String[] args) {
        String directory = ".";
        
        // Using printf to create a formatted command string.
        String command = String.format("ls -l %s", directory);

        // Executing the ls command using the system function.
        System.out.printf("Executing: %s\n", command);
        int result = System.system(command);  // Assuming a hypothetical system method that can execute commands.

        if (result != 0) {
            System.err.println("An error occurred while executing the command.");
        }
    }

    // Hypothetical implementation of System.system() to simulate command execution.
    static class System {
        public static int system(String cmd) {
            try {
                Process process = Runtime.getRuntime().exec(cmd);
                process.waitFor();
                return process.exitValue();
            } catch (Exception e) {
                e.printStackTrace();
                return -1;
            }
        }
    }
}