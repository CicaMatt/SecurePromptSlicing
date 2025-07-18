import java.io.*;
public class Main{
    public static void main(String[] args)throws Exception{
        String command="cat /etc/passwd | grep "+args[0];
        Process p=Runtime.getRuntime().exec(command);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}