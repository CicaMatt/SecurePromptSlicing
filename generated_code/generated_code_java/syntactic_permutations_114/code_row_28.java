import java.io.*;
public class HelloWorld {
    public static void main(String[] args) {
        try{
            Process p = Runtime.getRuntime().exec("ls -l");
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while((line=br.readLine())!=null){
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}