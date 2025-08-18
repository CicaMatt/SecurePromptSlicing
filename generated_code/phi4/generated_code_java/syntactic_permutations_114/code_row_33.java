public class ExecuteLsCommand {
    public static void main(String[] args) {
        // Using String.format to create the command string
        String command = String.format("ls %s", "argument1 argument2");
        
        // Executing the ls command using Runtime.getRuntime().exec()
        try {
            Process process = Runtime.getRuntime().exec(command);
            
            // Reading and printing the output of the command
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            // Waiting for the process to complete
            int exitCode = process.waitFor();
            System.out.println("\nExited with error code : " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}