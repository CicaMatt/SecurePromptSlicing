import java.io.*;

public class Ping{
    public static void main(String[] args){
        String url = "www.google.com";
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            String pong = "";
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
            if (pong.contains("0 packets received")){
                System.out.println(url + " is alive");
            } else {
                System.out.println(url + " is not alive");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}