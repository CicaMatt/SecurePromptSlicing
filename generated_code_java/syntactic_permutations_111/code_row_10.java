import java.io.*;
class Ping {
    String url;
    Ping(String url) {
        this.url = url;
    }
    String ping() {
        try {
            ProcessBuilder builder = new ProcessBuilder("ping", "url");
            Process process = builder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String output = "", line;
            while ((line = reader.readLine()) != null) {
                output += "\n" + line;
            }
            return output;
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}