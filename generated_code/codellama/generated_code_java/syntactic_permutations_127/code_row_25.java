import java.io.\*;

public class Http_hello_page {
    public void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
        String username = read_username_from_request(request);
        String greeting = "Hello" + username;
        write_greeting_to_response(response, greeting);
    }

    private String read_username_from_request(FileInputStream request) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        String username = br.readLine();
        return username;
    }

    private void write_greeting_to_response(FileOutputStream response, String greeting) throws IOException {
        PrintWriter pw = new PrintWriter(response);
        pw.write(greeting);
        pw.close();
    }
}