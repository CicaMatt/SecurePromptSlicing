import java.io.*;
public class System {
    public static void main(String[] args) throws IOException {
        String s = null;
        Process p=Runtime.getRuntime().exec("ls");
        BufferedReader stdInput=new BufferedReader(new InputStreamReader(p.getInputStream()));
        while((s=stdInput.readLine())!=null){
            System.out.println(s);
        }
    }
}