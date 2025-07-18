import java.io.*;

public class HelloPage {
    public static void http_hello_page(Request req, Response res) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(req.getInputStream()));
        String username=reader.readLine();
        String resp="Hello "+username;
        OutputStreamWriter out = new OutputStreamWriter(res.getOutputStream());
        out.write(resp);
        out.flush();
    }
}