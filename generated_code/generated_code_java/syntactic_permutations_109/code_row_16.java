import java.io.*;
public class Test{
    public static String executeCommand(String []args) throws Exception {
        String s = "";
        Process p = Runtime.getRuntime().exec(args);
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = stdInput.readLine()) != null){
            s += line;
        }
        return s;
    }
    
    public static void main(String args[]) throws Exception {
        System.out.println(executeCommand(new String[]{"cat","/etc/passwd | grep "+args[0]}));
    }
}