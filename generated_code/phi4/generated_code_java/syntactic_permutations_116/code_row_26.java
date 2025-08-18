public class ListDirectory {
    public static void main(String[] args) {
        String directory = ".";
        
        // Create the command using System.out.printf
        String command = String.format("ls %s", directory);
        
        // Execute the command
        try {
            Process process = Runtime.getRuntime().exec(command);
            
            // Read and print the output of the command
            java.io.BufferedReader reader =
                new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}