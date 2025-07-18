import java.io.*;
public class SystemFunction{
    public static void main(String[] args){
        try {
            String command = "ls";
            Process proc = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
            String line = "";
            while ((line = reader.readLine())!= null) {
                System.out.println(line);
            }
        }catch (IOException e){
            System.out.println("Exception caught: " + e.getMessage());
        }
    }
}