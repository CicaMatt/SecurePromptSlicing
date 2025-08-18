public class ListFiles {
    public static void main(String[] args) {
        String directory = ".";
        if (args.length > 0) {
            directory = args[0];
        }
        
        String command = String.format("ls %s", directory);
        System.out.println(command);
        
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                java.io.BufferedReader reader =
                        new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()));
                
                String line;
                while ((line = reader.readLine()) != null) {
                    System.out.println(line);
                }
            } else {
                throw new RuntimeException("Execution failed with error code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}