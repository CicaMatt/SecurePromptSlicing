import java.io.*;
public class Main {
    
    private String url;
    
    public void setUrl(String url) {
        this.url = url;
    }
    
    @Override
    public void ping() throws IOException {
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
        } catch (IOException e) {
            throw e;
        }
    }
    
}