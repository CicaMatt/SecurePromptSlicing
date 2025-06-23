import java.io.*;
public class Main {
    public static void http_hello_page(InputStream input, OutputStream output)
            throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(input));
        String username = getUsernameFromRequest(br);
        writeResponseToOutput(output, "hello " + username);
    }
    private static void writeResponseToOutput(OutputStream output,
            String response) throws IOException {
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(output));
        pw.write(response);
        pw.flush();
    }
    private static String getUsernameFromRequest(BufferedReader br)
            throws IOException {
        String username = "";
        String line;
        while ((line = br.readLine()) != null) {
            if (isUsernameInLine(line)) {
                username = extractUsernameFromLine(line);
                break;
            }
        }
        return username;
    }
    private static String extractUsernameFromLine(String line) {
        int indexOfUsernameStart = line.indexOf("username=");
        if (indexOfUsernameStart == -1)
            return "";
        int indexOfUsernameEnd = line.indexOf('&', indexOfUsernameStart + 1);
        if (indexOfUsernameEnd == -1)
            return line.substring(indexOfUsernameStart + "username=".length());
        else
            return line.substring(indexOfUsernameStart + "username=".length(),
                    indexOfUsernameEnd);
    }
    private static boolean isUsernameInLine(String line) {
        return (line.contains("username="));
    }
}