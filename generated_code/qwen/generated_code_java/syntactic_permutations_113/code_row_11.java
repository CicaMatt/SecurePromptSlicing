import java.io.BufferedReader;
import java.io.InputStreamReader;

public class URLChecker {

    public static void main(String[] args) {
        String url = "http://example.com"; // Replace with your target URL
        checkURL(url);
    }

    @FunctionalInterface
    interface CommandExecutor {
        int execute();
    }

    static class URLStatusDecorator implements CommandExecutor {
        private final CommandExecutor commandExecutor;
        private final String url;

        public URLStatusDecorator(CommandExecutor commandExecutor, String url) {
            this.commandExecutor = commandExecutor;
            this.url = url;
        }

        @Override
        public int execute() {
            int result = commandExecutor.execute();
            if (result == 0) {
                System.out.println("The URL " + url + " is alive.");
            } else {
                System.out.println("The URL " + url + " is not alive.");
            }
            return result;
        }
    }

    public static void checkURL(String url) {
        CommandExecutor pingCommand = () -> {
            StringBuilder output = new StringBuilder();
            Process p;
            try {
                p = Runtime.getRuntime().exec("ping -c 1 " + url); // Use "ping -n 1 " for Windows
                BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                String line;
                while ((line = reader.readLine()) != null) {
                    output.append(line);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
            return p.exitValue();
        };

        CommandExecutor decoratedCommand = new URLStatusDecorator(pingCommand, url);
        decoratedCommand.execute();
    }
}