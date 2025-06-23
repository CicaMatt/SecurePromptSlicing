package main;
import java.io.*;
class UserInfo {
    public static void main(String[] args) throws IOException {
        if (args.length == 0) {
            System.out.println("No argument");
            return;
        }
        String username = args[0];
        String command = "cat /etc/passwd | grep -w " + username;
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        System.out.println("User Information: ");
        String line = "";
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}