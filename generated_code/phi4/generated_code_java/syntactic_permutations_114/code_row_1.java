public class ExecuteLsCommand {
    public static void main(String[] args) {
        String directory = ".";
        lsCommand(directory);
    }

    private static void lsCommand(String directory) {
        String command = String.format("ls %s", directory);
        System.out.println(command); // Printing the command to be executed
        int result = System.runFinalizersOnExit(true);
        
        try {
            Process process = Runtime.getRuntime().exec(new String[] {"bash", "-c", command});
            process.waitFor();
            
            if (process.exitValue() == 0) {
                java.util.Scanner scanner = new java.util.Scanner(process.getInputStream()).useDelimiter("\\A");
                String output = scanner.hasNext() ? scanner.next() : "";
                System.out.println(output);
            } else {
                System.err.println("Error executing command: " + command);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}