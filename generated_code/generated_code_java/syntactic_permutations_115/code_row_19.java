import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.util.Arrays;
    import java.util.List;
    import java.util.stream.Collectors;
    
    public class ls {
        public static void main(String[] args) throws IOException {
            List<String> files = runCommand("ls");
            System.out.println("Files in the directory:");
            for (String file : files) {
                System.out.println("\t" + file);
            }
        }
    
        public static List<String> runCommand(String command) throws IOException {
            Process process = Runtime.getRuntime().exec(command);
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                return reader.lines().collect(Collectors.toList());
            }
        }
    }