import java.io.*;
public class HelloWorld{
    public static void main(String[] args){
        String command = "ls";
        System.out.println("Executing command: "+command);
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e){
            System.out.println("Unable to execute command: " +command);
            System.out.println(e.getMessage());
        }
    }
}