import java.io.*;
public class Main {
    public static void executeCommand(String cmd){
        Process process = null;
        try{
            process = Runtime.getRuntime().exec(cmd);
        } catch (Exception e) {
            System.out.println("An error occured");
            return;
        }
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line = "";
        while((line=reader.readLine())!=null){
            System.out.println(line);
        }
    }
    public static void main(String[] args) {
        executeCommand("cat /etc/passwd | grep " + args[0]);
    }
}