import java.io.*;
public class Ping {
    public static String ping(String url) throws IOException{
        Runtime rt = Runtime.getRuntime();
        Process p = rt.exec("ping " + url);
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String output;
        while((output = br.readLine())!=null){
            System.out.println(output);
        }
        return output;
    }
}