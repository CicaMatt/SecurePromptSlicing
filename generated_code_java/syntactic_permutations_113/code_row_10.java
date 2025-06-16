import java.io.*;
import java.net.*;
public class Ping {
    private String url;
    public void ping() throws IOException{
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping " + url);
        BufferedReader br = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        String line;
        StringBuilder sb = new StringBuilder();
        while ((line = br.readLine())!=null){
            sb.append(line + "\n");
        }
        pr.waitFor();
        int exitVal = pr.exitValue();
        if (exitVal == 0) {
            System.out.println("URL is alive.");
        } else{
            System.out.println("URL not alive.");
        }
    }
}