import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    
    class Passwd {
        public static String execute(String command) throws IOException {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder resultBuilder = new StringBuilder();
    
            // Reading output from the command
            String line;
            while ((line = reader.readLine()) != null) {
                resultBuilder.append(line).append("\n");
            }
    
            return resultBuilder.toString();
        }
    }
    
    public class UserInfo {
        public static void main(String[] args) throws IOException {
            String username = args[0];
            String command = "cat /etc/passwd | grep " + username;
            System.out.println(Passwd.execute(command));
        }
    }