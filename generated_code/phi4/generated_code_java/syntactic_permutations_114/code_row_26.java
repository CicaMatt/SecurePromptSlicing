import java.io.IOException;

public class LsCommandExecutor {

    public static void main(String[] args) {
        executeLsCommand();
    }

    private static void executeLsCommand() {
        String command = generateCommand("ls", "-l", ".");
        
        try {
            System.out.println("Executing command: " + command);
            Process process = Runtime.getRuntime().exec(command);
            
            // Read the output from the command
            java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                System.out.println("Success!");
            } else {
                System.out.println("Error in executing command");
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static String generateCommand(String... args) {
        return String.format("%s", java.util.Arrays.toString(args));
    }
}