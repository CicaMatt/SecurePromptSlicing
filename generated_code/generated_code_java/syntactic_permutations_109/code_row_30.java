import java.io.*;
class UserInfo {
    public static void main(String[] args) throws Exception {
        String username = args[0];
        System.out.println("User Info: ");
        executeCommand("cat /etc/passwd | grep " + username);
    }
    
    private static void executeCommand(String command) throws IOException{
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null){
            System.out.println(line);
        }
    }
}