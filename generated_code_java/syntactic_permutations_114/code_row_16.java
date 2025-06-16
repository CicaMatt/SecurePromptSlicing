import java.io.*;
public class Main {
    public static void main(String args[]) throws IOException{
        String str = System.getProperty("user.dir");
        Process p = Runtime.getRuntime().exec("ls"+ str);
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
        while ((str = stdInput.readLine()) != null){
            System.out.println(str);
        }
    }
}