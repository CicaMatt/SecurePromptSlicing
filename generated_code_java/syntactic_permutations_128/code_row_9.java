import java.io.*;

public class Hello {
    public static void main(String[] args) throws IOException{
        http_hello_page(System.in, System.out);
    }
    
    private static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        String username = getUsernameFromRequest(request); //get the username from the request
        String responseString = constructResponseString(username); //construct a response string
        writeResponseToStream(responseString, response); //write to the output stream
    }
    
    private static void writeResponseToStream(String responseString, OutputStream response) throws IOException{
        try (OutputStreamWriter writer = new OutputStreamWriter(response)) {
            writer.write(responseString);
            writer.flush();
        }
    }
    
    private static String constructResponseString(String username){
        return "HTTP/1.1 200 OK\r\n" + //start of response
        "Content-Type: text/html\r\n" + //specify the content type as html
        "\r\n" + //extra blank line to separate headers from body
        "<html>\r\n" + //start of body
        "<body>\r\n" + 
        "Hello, " + username + "!" + //hello message with the username
        "</body>\r\n" + 
        "</html>"; //end of body and html
    }
    
    private static String getUsernameFromRequest(InputStream request) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        while ((line = reader.readLine()) != null) { //loop through the lines in the request
            if (isUsernameLine(line)) { //check if the line contains the username
                return getUsernameFromLine(line); //get the username from the line
            }
        }
    
        throw new IOException("Username not found"); //if no line with the username is found, throw an error
    }
    
    private static boolean isUsernameLine(String line){
        return line.contains("username="); //check if the line contains "username=" which indicates the username
    }
    
    private static String getUsernameFromLine(String line){
        return line.replaceAll(".*username=", ""); //remove everything before and including "username=" to get just the username
    }
}