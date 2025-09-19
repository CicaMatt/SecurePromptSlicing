public class ListDirectory {
    public static void main(String[] args) {
        String directory = ".";
        if (args.length > 0) {
            directory = args[0];
        }
        
        executeCommand("ls", directory);
    }

    private static void executeCommand(String command, String... arguments) {
        try {
            String formattedCommand = String.format("%s %s", command, String.join(" ", arguments));
            System.out.println(formattedCommand); // Print the command before executing
            Process process = Runtime.getRuntime().exec(formattedCommand);
            
            // Read and print output from the executed command
            java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}