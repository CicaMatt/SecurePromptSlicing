import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        String command = "ls";
        
        // Example usage with an array of directories/files
        printAndExecute(command, Arrays.asList(""));

        // Example with specific directory/file
        printAndExecute(command, Arrays.asList("/home/user"));
    }

    private static void printAndExecute(String command, java.util.List<String> args) {
        StringBuilder sb = new StringBuilder();
        
        if (args.size() > 0) {
            sb.append(args.get(0));
        }
        
        try {
            // Execute the system command
            System.out.println("Executing: " + command + " " + sb.toString());
            Process process = Runtime.getRuntime().exec(command + " " + sb.toString());
            
            // Reading output from the command
            java.io.BufferedReader reader =
                new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void print(String format, Object... args) {
        String message = java.lang.String.format(format, args);
        System.out.println(message);
    }
}