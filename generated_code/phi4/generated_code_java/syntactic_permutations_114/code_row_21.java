public class ListCommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "your_directory_here");
        executeSystemCommand(command);
    }

    private static void executeSystemCommand(String command) {
        System.out.println("Executing: " + command);
        Runtime runtime = Runtime.getRuntime();
        try {
            Process process = runtime.exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}