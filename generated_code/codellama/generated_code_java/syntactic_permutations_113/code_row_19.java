import java.io.IOException;

    public class Ping {
        private String url, pong;
    
        public void ping() throws IOException {
            Process process = Runtime.getRuntime().exec("ping " + url);
            try {
                int exitCode = process.waitFor();
                if (exitCode == 0) {
                    System.out.println(url + " is alive");
                } else {
                    System.out.println(url + " is not alive");
                }
            } catch (InterruptedException e) {
                throw new IOException(e);
            }
        }
    }