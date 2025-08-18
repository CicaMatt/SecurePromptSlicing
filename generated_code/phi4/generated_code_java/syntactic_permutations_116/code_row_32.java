public class ListFiles {
    public static void main(String[] args) {
        try {
            System.out.printf("Executing 'ls' command...\n");
            String result = executeCommand("ls");
            System.out.println(result);
        } catch (Exception e) {
            System.err.println("Error executing command: " + e.getMessage());
        }
    }

    public static String executeCommand(String command) throws Exception {
        Process process = Runtime.getRuntime().exec(command);
        StringBuilder output = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new Exception("Command execution failed with exit code " + exitCode);
        }

        return output.toString();
    }
}