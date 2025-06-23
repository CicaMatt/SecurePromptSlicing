import java.io.*; 

public class Ping {
    public String ping() {
        String url = "";
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String inputLine;
            StringBuilder response = new StringBuilder();

            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }
            in.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return url;
    }
}