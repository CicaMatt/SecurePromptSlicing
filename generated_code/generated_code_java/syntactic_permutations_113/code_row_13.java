import java.io.*;
class PingDecorator {
    public void decorate(String url) throws Exception{
        Process p = Runtime.getRuntime().exec("ping -c 3 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        StringBuilder response = new StringBuilder();
        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();
        if (response.toString().contains(" 0% packet loss")){
            System.out.println("URL is alive");
        } else{
            System.out.println("URL is not alive");
        }
    }
}
public class Main {
    public static void main(String[] args) throws Exception{
        String url = "google.com";
        PingDecorator pd = new PingDecorator();
        pd.decorate(url);
    }
}