import java.io.BufferedReader;
    import java.io.InputStreamReader;

    public class Main {
        public static void main(String[] args) throws Exception {
            String cmd = "id " + args[0];
            Process p = Runtime.getRuntime().exec(cmd);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = p.waitFor();
            System.out.println("\n\nExit Code: " + exitCode);
        }
    }