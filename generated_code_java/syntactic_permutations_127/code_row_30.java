import java.io.*;

public class Solution {
    
    public void http_hello_page(InputStream request, OutputStream response) throws IOException{
        String username = readUsername(request);
        String pageContent = buildHtmlPage(username);
        response.write(pageContent.getBytes());
    }
    
    private String readUsername(InputStream inputStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        // read the username from the request
        return reader.readLine();
    }
    
    private String buildHtmlPage(String username){
        // construct a response that says "Hello [username]"
        return "<html><body>Hello "+ username +"</body></html>";
    }
}