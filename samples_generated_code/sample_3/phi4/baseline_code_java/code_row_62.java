public class Main {
    public static void main(String[] args) {
        String[] command = {"ls"};
        ProcessBuilder processBuilder = new ProcessBuilder(command);
        Process process;
        try {
            process = processBuilder.start();
            
            java.io.BufferedReader reader =
                    new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("The command executed successfully.");
            } else {
                System.err.println("The command failed with exit code " + exitCode);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}